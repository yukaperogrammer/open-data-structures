#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "rootish_array_stack.h"

#define TRUE 1
#define FALSE 0

/*
rootish array stack初期化
*/
int rarray_stack_init(rarray_stack *ras)
{
    ras->blocks = NULL;
    ras->num_of_element = 0;
    ras->num_of_block = 0;
    ras->next_block_length = 1;

    if (grow(ras) == FALSE)
    {
        /*初期化失敗*/
        return FALSE;
    }

    return TRUE;
}

/*
rootish array stack解放
*/
void rarray_stack_free(rarray_stack *ras)
{
    int i;

    for (i = 0; i < ras->num_of_block; i++)
    {
        free(ras->blocks[i]->array);
        free(ras->blocks[i]);
    }

    free(ras->blocks);
}

/*
要素の取得
*/
char *rarray_stack_get(rarray_stack *ras, int offset)
{
    int offset_in_block;
    int boffset;

    if (offset >= ras->num_of_element || offset < 0)
    {
        /* 適切なインデックス範囲ではないので、NULL */
        return NULL;
    }

    boffset = offset_to_boffset(offset);
    offset_in_block = offset - boffset * (boffset + 1) / 2;

    return ras->blocks[boffset]->array[offset_in_block];
}

/*
要素のセット
*/
char *rarray_stack_set(rarray_stack *ras, int offset, char *element)
{
    char *old_element;
    int offset_in_block;
    int boffset;

    if (offset > ras->num_of_element || offset < 0)
    {
        /* 適切なインデックス範囲ではないので、NULL */
        return NULL;
    }

    boffset = offset_to_boffset(offset);
    offset_in_block = offset - boffset * (boffset + 1) / 2;

    old_element = ras->blocks[boffset]->array[offset_in_block];
    ras->blocks[boffset]->array[offset_in_block] = element;
    
    return old_element;
}

/*
要素の追加
*/
int rarray_stack_add(rarray_stack *ras, int offset, char *element)
{
    int i;

    if (is_full(ras))
    {
        if (grow(ras) == FALSE)
        {
            /* 拡張に失敗して追加できないので、FALSE */
            return FALSE;
        }
    }

    if (offset > ras->num_of_element || offset < 0)
    {
        /* 適切なインデックス範囲ではないので、FALSE */
        return FALSE;
    }

    for (i = ras->num_of_element; i > offset; i--)
    {
        rarray_stack_set(ras, i, rarray_stack_get(ras, i - 1));
    }
    rarray_stack_set(ras, offset, element);

    ras->num_of_element++;

    return TRUE;
}

/*
末尾に要素の追加
*/
int rarray_stack_push(rarray_stack *ras, char *element)
{
    return rarray_stack_add(ras, ras->num_of_element, element);
}

/*
要素の削除
*/
char *rarray_stack_remove(rarray_stack *ras, int offset)
{
    char *element;
    int i;

    if (is_empty(ras))
    {
        /* 要素が空なので、NULL */
        return NULL;
    }

    if (offset >= ras->num_of_element || offset < 0)
    {
        /* 適切なインデックス範囲ではないので、NULL */
        return NULL;
    }

    element = rarray_stack_get(ras, offset);
    
    for (i = offset; i < ras->num_of_element - 1; i++)
    {
        rarray_stack_set(ras, i, rarray_stack_get(ras, i + 1));
    }
    rarray_stack_set(ras, i, NULL);

    ras->num_of_element--;

    shrink(ras);

    return element;
}

/*
末尾の要素を削除
*/
char *rarray_stack_pop(rarray_stack *ras)
{
    return rarray_stack_remove(ras, ras->num_of_element - 1);
}

/*
rootish array stackの全要素を表示
*/
void rarray_stack_show(rarray_stack *ras)
{
    int i;
    int boffset;
    int offset_in_block;

    printf("<<<show rootish array stack elements>>>\n");
    for (i = 0; i < ras->num_of_element; i++)
    {
        boffset = offset_to_boffset(i);
        offset_in_block = i - boffset * (boffset + 1) / 2;

        printf("element: %s (offset of box = %d, offset in block = %d)\n", ras->blocks[boffset]->array[offset_in_block], boffset, offset_in_block);
    }
    printf("\n");
}

/*
offsetからboxのoffsetを計算
*/
int offset_to_boffset(int offset)
{
    double db = (-3.0 + sqrt(9 + 8 * offset)) / 2.0;

    return (int)ceil(db);
}

/*
ブロックの追加
*/
int grow(rarray_stack *ras)
{
    block **bp;
    int i;

    /* blocksの領域を1個分拡張 */
    bp = (block **)xmalloc(ras->blocks, sizeof(block *) * (ras->num_of_block + 1));
    if (bp == NULL)
    {
        /* メモリ確保失敗、FALSE */
        return FALSE;
    }

    /* block1個分の領域確保 */
    bp[ras->num_of_block] = (block *)xmalloc(NULL, sizeof(block));
    if (bp[ras->num_of_block] == NULL)
    {
        /* メモリ確保失敗、FALSE */
        free(bp);
        return FALSE;
    }

    /* 要素を格納する配列の領域確保 */
    bp[ras->num_of_block]->array = (char **)xmalloc(NULL, sizeof(char *) * ras->next_block_length);
    if (bp[ras->num_of_block]->array == NULL)
    {
        /* メモリ確保失敗、FALSE */
        free(bp[ras->num_of_block]);
        free(bp);
        return FALSE;
    }

    /* NULLで初期化 */
    for (i = 0; i < ras->next_block_length; i++)
    {
        bp[ras->num_of_block]->array[i] = NULL;
    }

    /* 全て確保できたので、元のポインタに代入 */
    ras->blocks = bp;

    /* ステータスの更新 */
    ras->num_of_block++;
    ras->next_block_length++;

    return TRUE;
}

/*
不要なブロックの削除
*/
int shrink(rarray_stack *ras)
{
    block **tmp;
    int sum = (ras->next_block_length - 3) * (ras->next_block_length - 2) / 2;

    if (ras->num_of_element > sum)
    {
        /* ブロック2つ以上の空きはなし、収縮しないのでFALSE */
        return FALSE;
    }

    free(ras->blocks[ras->num_of_block - 1]->array);
    free(ras->blocks[ras->num_of_block - 1]);

    tmp = (block **)xmalloc(ras->blocks, sizeof(block *) * (ras->num_of_block - 1));
    if (tmp == NULL)
    {
        /* 領域の収縮失敗、FALSE */
        return FALSE;
    }
    ras->blocks = tmp;

    ras->num_of_block--;
    ras->next_block_length--;

    return TRUE;
}

/*
配列が空か判定
*/
int is_empty(rarray_stack *ras)
{
    if (ras->num_of_element == 0)
    {
        return TRUE;
    }

    return FALSE;
}

/*
配列がいっぱいか判定
*/
int is_full(rarray_stack *ras)
{
    int total_element = (ras->next_block_length - 1) * ras->next_block_length / 2;

    if (ras->num_of_element == total_element)
    {
        return TRUE;
    }

    return FALSE;
}

/*
メモリの動的確保を行う
*/
void *xmalloc(void *ptr, int size)
{
    void *p;

    if (ptr == NULL)
    {
        p = malloc(size);
    }
    else
    {
        p = realloc(ptr, size);
    }

    return p;
}


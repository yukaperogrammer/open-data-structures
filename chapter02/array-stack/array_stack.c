#include <stdio.h>
#include <stdlib.h>
#include "array_stack.h"

#define TRUE 1
#define FALSE 0

/*
array stackを初期化する。
lengthに指定された分の配列を作成。
*/
void array_stack_init(array_stack *asp, int length)
{
    backing_array_init(&asp->barr, length);
    asp->num_of_element = 0;
}

/*
array stackに格納されている要素の数を返す。
*/
int array_stack_size(array_stack *asp)
{
    return asp->num_of_element;
}

/*
offsetインデックスの要素を返す。
*/
char *array_stack_get(array_stack *asp, int offset)
{
    if (offset >= asp->num_of_element || offset < 0)
    {
        /* 適切なインデックス範囲ではないのでNULL*/
        fprintf(stderr, "offset out of range\n");
        return NULL;
    }

    return asp->barr.array[offset];
}

/*
offsetインデックスの要素をnew_elementで上書きする。
上書きに成功したら前の要素の値を返す。
*/
char *array_stack_set(array_stack *asp, int offset, char *new_element)
{
    char *old_element;

    if (offset >= asp->num_of_element || offset < 0)
    {
        /* 適切なインデックス範囲ではないのでNULL */
        fprintf(stderr, "offset out of range\n");
        return NULL;
    }

    old_element = asp->barr.array[offset];
    asp->barr.array[offset] = new_element;

    return old_element; 
}

/*
offsetインデックスにnew_elementを追加する。
*/
int array_stack_add(array_stack *asp, int offset, char *new_element)
{
    int i;

    /* 配列がfullだったら拡張 */
    if (asp->num_of_element == asp->barr.length)
    {
        if (array_stack_resize(asp) == FALSE)
        {
            /* 拡張失敗なら追加できないのでFALSE */
            fprintf(stderr, "memory is not extend\n");
            return FALSE;
        }
    }

    if (offset > asp->num_of_element || offset < 0)
    {
        /* 適切なインデックス範囲ではないのでFALSE */
        fprintf(stderr, "offset out of range\n");
        return FALSE;
    }

    /* 要素を1つずらしてoffsetインデックスに要素を追加 */
    for (i = asp->num_of_element - 1; i >= offset; i--)
    {
        asp->barr.array[i + 1] = asp->barr.array[i];
    }
    asp->barr.array[offset] = new_element;

    /* 要素が1つ増えたのでサイズを増やす */
    asp->num_of_element++;

    return TRUE;
}

/*
offsetインデックスの要素を削除する。
*/
char *array_stack_remove(array_stack *asp, int offset)
{
    int i;
    char *retval;

    if (offset >= asp->num_of_element || offset < 0)
    {
        /* 適切なインデックス範囲ではないのでNULL */
        fprintf(stderr, "offset out of range\n");
        return NULL;
    }

    retval = asp->barr.array[offset];

    for (i = offset; i < asp->num_of_element - 1; i++)
    {
        asp->barr.array[i] = asp->barr.array[i + 1];
    }

    /* 一応NULLで埋めておく */
    asp->barr.array[i] = NULL;

    /* 要素が1つ減ったのでサイズを減らす */
    asp->num_of_element--;

    return retval;
}

/*
要素を格納するための配列を拡張する。
*/
int array_stack_resize(array_stack *asp)
{
    int i;
    char **tmp;

    /* 2倍の大きさに拡張 */
    tmp = (char **)xmalloc(asp->barr.array, sizeof(char *) * 2 * asp->barr.length);
    if (tmp == NULL)
    {
        return FALSE;
    }

    /* 一応NULLで初期化しておく */
    for (i = asp->barr.length; i < 2 * asp->barr.length; i++)
    {
        tmp[i] = NULL;
    }

    asp->barr.array = tmp;
    asp->barr.length *= 2;

    return TRUE;
}

/*
array stackを解放する。
*/
void array_stack_free(array_stack *asp)
{
    backing_array_free(&asp->barr);
}

/*
array stackに格納されている全要素を表示。
*/
void array_stack_show(array_stack *asp)
{
    int i;

    printf("<<<show array stack elements>>>\n");
    for (i = 0; i < asp->num_of_element; i++)
    {
        printf("element: %s\n", asp->barr.array[i]);
    }
    printf("\n");
}


#include <stdio.h>
#include <stdlib.h>
#include "array_deque.h"

#define TRUE 1
#define FALSE 0

/*
array dequeを初期化。
lengthに指定した分の配列を持つ。
*/
int array_deque_init(array_deque *ad, int length)
{
    int i;

    if (length <= 0)
    {
        /* 配列の大きさがマイナスならFALSE */
        fprintf(stderr, "invaid length\n");
        return FALSE;
    }

    ad->array = (char **)xmalloc(NULL, sizeof(char *) * length);
    if (ad->array == NULL)
    {
        /* メモリ確保に失敗したのでFALSE */
        fprintf(stderr, "memory allocate failed\n");
        return FALSE;
    }

    for (i = 0; i < length; i++)
    {
        ad->array[i] = NULL;
    }
    ad->length = length;
    ad->num_of_element = 0;
    ad->head = 0;
    ad->tail = 1;

    return TRUE;
}

/*
array dequeを解放。
*/
void array_deque_free(array_deque *ad)
{
    free(ad->array);
}

/*
array dequeのサイズ（要素数）を返す。
*/
int array_deque_size(array_deque *ad)
{
    return ad->num_of_element;
}

/*
offsetインデックスの要素を返す。
存在するならその要素を、しないならNULLを返す。
*/
char *array_deque_get(array_deque *ad, int offset)
{
    int index;

    if (offset >= ad->num_of_element || offset < 0)
    {
        /* 適切なインデックス範囲ではないのでNULL */
        fprintf(stderr, "offset out of range\n");
        return NULL;
    }

    index = ((ad->head + 1) + offset) % ad->length;

    return ad->array[index];
}

/*
offsetインデックスの要素をelementで上書きする。
上書きできたら上書き前の要素を、上書きできなかったらNULLを返す。
*/
char *array_deque_set(array_deque *ad, int offset, char *element)
{
    int index;
    char *tmp;

    if (offset >= ad->num_of_element || offset < 0)
    {
        /* 適切なインデックス範囲ではないのでNULL */
        fprintf(stderr, "offset out of range\n");
        return NULL;
    }

    index = ((ad->head + 1) + offset) % ad->length;
    tmp = ad->array[index];
    ad->array[index] = element;

    return tmp;
}

/*
offsetインデックスにelementを追加する。
追加できればTRUEを、できなければFALSEを返す。
*/
int array_deque_add(array_deque *ad, int offset, char *element)
{
    int offset_center;
    int i;

    if (is_full(ad))
    {
        /* これ以上追加できないのでFALSE */
        fprintf(stderr, "array deque is full\n");
        return FALSE;
    }

    if (offset > ad->num_of_element || offset < 0)
    {
        /* 適切なインデックス範囲ではないのでFALSE */
        fprintf(stderr, "offset out of range\n");
        return FALSE;
    }

    /* 真ん中からの偏りでどちらにずらすか決める */
    offset_center = ad->num_of_element / 2;
    if (offset < offset_center)
    {
        /* 左にずらす */
        for (i = 0; i < offset; i++)
        {
            ad->array[mod(ad->head + i, ad->length)] = ad->array[mod(ad->head + 1 + i, ad->length)];
        }
        ad->array[mod(ad->head + i, ad->length)] = element;
        ad->head = mod(ad->head - 1, ad->length);
    }
    else
    {
        /* 右にずらす */
        for (i = 0; i < ad->num_of_element - offset; i++)
        {
            ad->array[mod(ad->tail - i, ad->length)] = ad->array[mod(ad->tail - 1 - i, ad->length)];
        }

        ad->array[mod(ad->tail - i, ad->length)] = element;
        ad->tail = mod(ad->tail + 1, ad->length);
    }

    ad->num_of_element++;

    return TRUE;
}

/*
offsetインデックスを削除する。
削除できればその要素を、できなければNULLを返す。
*/
char *array_deque_remove(array_deque *ad, int offset)
{
    char *element;
    int offset_center;
    int i;

    if (is_empty(ad))
    {
        /* 空なのでFALSE */
        fprintf(stderr, "array deque is empty\n");
        return NULL;
    }

    if (offset >= ad->num_of_element || offset < 0)
    {
        /* 適切なインデックス範囲ではないのでNULL */
        fprintf(stderr, "offset out of range\n");
        return NULL;
    }

    /* 戻り値を保持 */
    element = ad->array[(ad->head + 1 + offset) % ad->length];

    /* 真ん中からの偏りでどちらをずらすか決める */
    offset_center = ad->num_of_element / 2;
    if (offset < offset_center)
    {
        /* 右にずらす */
        for (i = offset; i > 0; i--)
        {
            ad->array[mod(ad->head + 1 + i, ad->length)] = ad->array[mod(ad->head + i, ad->length)];
        }
        
        ad->head = mod(ad->head + 1, ad->length);
        ad->array[ad->head] = NULL;
    }
    else
    {
        /* 左にずらす */
        for (i = ad->num_of_element - offset - 1; i > 0; i--)
        {
            ad->array[mod(ad->tail - 1 - i, ad->length)] = ad->array[mod(ad->tail - i, ad->length)];
        }

        ad->tail = mod(ad->tail - 1, ad->length);
        ad->array[ad->tail] = NULL;
    }

    ad->num_of_element--;

    return element;
}

/*
array dequeの要素を順に表示する。
*/
void array_deque_show(array_deque *ad)
{
    int i;

    printf("<<<show array deque elements>>>\n");
    for (i = 0; i < ad->num_of_element; i++)
    {
        printf("element: %s\n", ad->array[(ad->head + 1 + i) % ad->length]);
    }
    printf("\n");
}

/*
array dequeが空か判定する。
空ならTRUEを、空ではないならFALSEを返す。
*/
int is_empty(array_deque *ad)
{
    if (ad->num_of_element == 0)
    {
        return TRUE;
    }

    return FALSE;
}

/*
array dequeがいっぱいか判定する。
いっぱいならTRUEを、空きがあるならFALSEを返す。
*/
int is_full(array_deque *ad)
{
    if (ad->num_of_element == ad->length)
    {
        return TRUE;
    }

    return FALSE;
}

/*
x を y で割った余りを返す。
マイナスにも対応。戻り値は常に非負。
*/
int mod(int x, int y)
{
    int r;

    r = x % y;
    if (r < 0)
    {
        r += y;
    }

    return r;
}

/*
メモリの動的確保を行う。
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


#include <stdio.h>
#include <stdlib.h>
#include  "backing_array.h"

#define TRUE 1
#define FALSE 0

/*
backing arrayを初期化する。
lengthに指定された分の配列を作成。
*/
int backing_array_init(backing_array *barr, int length)
{
    int i;

    if (length <= 0)
    {
        /* 長さの値が適切な範囲ではないのでFALSE */
        fprintf(stderr, "invalid array length\n");
        return FALSE;
    }

    barr->array = (char **)xmalloc(NULL, sizeof(char *) * length);
    if (barr->array == NULL)
    {
        /* メモリの確保失敗で初期化できないのでFALSE */
        fprintf(stderr, "memory allocate failed\n");
        return FALSE;
    }

    /* 一応NULLで初期化 */
    for (i = 0; i < length; i++)
    {
        barr->array[i] = NULL;
    }

    barr->length = length;

    return TRUE;
}

/*
backing arrayを解放する。
*/
void backing_array_free(backing_array *barr)
{
    free(barr->array);
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


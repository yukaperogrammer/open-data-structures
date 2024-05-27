#include <stdio.h>
#include <stdlib.h>
#include "array_queue.h"

#define TRUE 1
#define FALSE 0

/*
array queueの初期化。
lengthに指定した分の配列を作成。
*/
int array_queue_init(array_queue *aq, int length)
{
    int i = 0;

    if (length < 0)
    {
        /* 負の数はFALSE */
        fprintf(stderr, "length is negative number\n");
        return FALSE;
    }

    aq->array = (char **)xmalloc(NULL, sizeof(char *) * length);
    if (aq->array == NULL)
    {
        /* メモリの確保失敗はFALSE */
        fprintf(stderr, "memory allocate failed\n");
        return FALSE;
    }

    /* NULLで初期化しておく */
    for (i = 0; i < length; i++)
    {
        aq->array[i] = NULL;
    }

    aq->length = length;
    aq->head = 0;
    aq->tail = 0;
    aq->num_of_element = 0;

    return TRUE;
}

/*
array queueの解放。
*/
void array_queue_free(array_queue *aq)
{
    free(aq->array);
}

/*
array queueに格納されている要素の数を返す。
*/
int array_queue_size(array_queue *aq)
{
    return aq->num_of_element;
}

/*
要素の追加。
追加できればTRUE、できなければFALSEを返す。
*/
int array_queue_add(array_queue *aq, char *element)
{
    if (is_full(aq))
    {
        /* 配列がいっぱいで追加できないのでFALSE */
        fprintf(stderr, "array queue is full\n");
        return FALSE;
    }

    /* 末尾に追加 */
    aq->array[aq->tail] = element;

    /* 除算でインデックスの範囲を 0 ~ aq.length の範囲に収める */
    aq->tail = (aq->tail + 1) % aq->length;

    aq->num_of_element++;

    return TRUE;
}

/*
要素の削除。
削除できればその要素を、できなければNULLを返す。
*/
char *array_queue_remove(array_queue *aq)
{
    char *element;

    if (is_empty(aq))
    {
        /* 配列が空なのでNULL */
        fprintf(stderr, "array queue is empty\n");
        return NULL;
    }

    /* 先頭の値を一旦保持 */
    element = aq->array[aq->head];

    /* NULLで埋めておく */
    aq->array[aq->head] = NULL;

    /* 除算でインデックスの範囲を 0 ~ aq.length の範囲に収める */
    aq->head = (aq->head + 1) % aq->length;

    aq->num_of_element--;

    return element;
}

/*
array queueが空かどうか調べる。
空ならTRUE、要素があるならFALSE。
*/
int is_empty(array_queue *aq)
{
    if (aq->num_of_element == 0)
    {
        return TRUE; 
    }

    return FALSE;
}

/*
array queueがいっぱいかどうか調べる。
いっぱいならTRUE、まだ追加できるならFALSE。
*/
int is_full(array_queue *aq)
{
    if (aq->num_of_element == aq->length)
    {
        return TRUE;
    }

    return FALSE;
}

/*
array queueの全要素を表示。
*/
void array_queue_show(array_queue *aq)
{
    int i;

    printf("<<<show array queue elements>>>\n");
    if (is_empty(aq))
    {
        printf("array queue is empty\n");
    }

    for (i = 0; i < aq->num_of_element; i++)
    {
        printf("element: %s\n", aq->array[(aq->head + i) % aq->length]);
    }
    printf("\n");
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


#include <stdio.h>
#include <stdlib.h>
#include "array_stack.h"

#define TRUE 1
#define FALSE 0

int array_stack_init(array_stack *as, int length)
{
    int i;

    if (length <= 0)
    {
        /* サイズの指定が不正な値なのでFALSE */
        return FALSE;
    }

    as->array = (char **)xmalloc(NULL, sizeof(char *) * length);
    if (as->array == NULL)
    {
        /* メモリの確保失敗なのでFALSE */
        return FALSE;
    }

    for (i = 0; i < length; i++)
    {
        as->array[i] = NULL;
    }

    as->length = length;
    as->num_of_element = 0;

    return TRUE;
}

void array_stack_free(array_stack *as)
{
    free(as->array);
}

int array_stack_size(array_stack *as)
{
    return as->num_of_element;
}

char *array_stack_get(array_stack *as, int offset)
{
    if (offset >= as->num_of_element || offset < 0)
    {
        /* offsetが有効な範囲ではないのでNULL */
        return NULL;
    }

    return as->array[offset];
}

char *array_stack_set(array_stack *as, int offset, char *element)
{
    char *tmp;

    if (offset >= as->num_of_element || offset < 0)
    {
        /* offsetが有効な範囲ではないのでNULL */
        return NULL;
    }

    tmp = as->array[offset];
    as->array[offset] = element;

    return tmp;
}

int array_stack_add(array_stack *as, int offset, char *element)
{
    int i;

    if (is_full(as))
    {
        if (array_stack_resize(as) == FALSE)
        {
            /* 配列のリサイズに失敗し、追加できないのでFALSE */
            return FALSE;
        }
    }

    if (offset > as->num_of_element || offset < 0)
    {
        /* offsetが有効な値ではないのでFALSE */
        return FALSE;
    }

    /* 右にずらす */
    for (i = as->num_of_element; i > offset; i--)
    {
        as->array[i] = as->array[i - 1];
    }
    as->array[i] = element;
    as->num_of_element++;

    return TRUE;
}

int array_stack_push(array_stack *as, char *element)
{
    return array_stack_add(as, as->num_of_element, element);
}

char *array_stack_remove(array_stack *as, int offset)
{
    int i;
    char *tmp;

    if (is_empty(as))
    {
        /* 空なのでNULL */
        return NULL;
    }

    if (offset >= as->num_of_element || offset < 0)
    {
        /* 有効な範囲ではないのでNULL */
        return NULL;
    }

    tmp = as->array[offset];

    /* 左にずらす */
    for (i = offset; i < as->num_of_element - 1; i++)
    {
        as->array[i] = as->array[i + 1];
    }

    as->array[i] = NULL;
    as->num_of_element--;

    /* 要素が少なくなってきたら配列を収縮 */
    if (3 * as->num_of_element <= as->length)
    {
        array_stack_resize(as);
    }

    return tmp;
}

char *array_stack_pop(array_stack *as)
{
    return array_stack_remove(as, as->num_of_element - 1);
}

void array_stack_show(array_stack *as)
{
    int i;

    printf("<<<show array stack elements>>>\n");
    for (i = 0; i < as->num_of_element; i++)
    {
        printf("element: %s\n", as->array[i]);
    }
    printf("\n");
}

int is_empty(array_stack *as)
{
    if (as->num_of_element == 0)
    {
        return TRUE;
    }

    return FALSE;
}

int is_full(array_stack *as)
{
    if (as->num_of_element == as->length)
    {
        return TRUE;
    }

    return FALSE;
}

int array_stack_resize(array_stack *as)
{
    char **tmp;
    int size;

    /* すぐにremoveしてしまうと配列のサイズが0になってしまうので、最低でも1つの領域は確保*/
    size = (2 * as->num_of_element) ? (2 * as->num_of_element) : 1;

    tmp = (char **)xmalloc(as->array, sizeof(char *) * size);
    if (tmp == NULL)
    {
        return FALSE;
    }

    as->array = tmp;
    as->length = size;

    return TRUE;
}

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


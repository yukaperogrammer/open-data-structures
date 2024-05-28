#include <stdio.h>
#include <stdlib.h>
#include "dual_array_deque.h"

#define TRUE 1
#define FALSE 0

/*
dual array dequeの初期化。
*/
int darray_deque_init(darray_deque *dd, int length)
{
    if (length <= 0)
    {
        /* 配列の大きさが不正 */
        return FALSE;
    }

    array_stack_init(&dd->front, length);
    array_stack_init(&dd->back, length);

    return TRUE;
}

/*
dual array dequeの解放。
*/
void darray_deque_free(darray_deque *dd)
{
    free(dd->front.array);
    free(dd->back.array);
}

/*
dual array dequeのサイズを返す。（2つの配列のサイズの合計）
*/
int darray_deque_size(darray_deque *dd)
{
    return array_stack_size(&dd->front) + array_stack_size(&dd->back);
}

/*
要素を取得。
*/
char *darray_deque_get(darray_deque *dd, int offset)
{
    if (offset < array_stack_size(&dd->front))
    {
        return array_stack_get(&dd->front, (array_stack_size(&dd->front) - offset - 1));
    }
    else
    {
        return array_stack_get(&dd->back, (offset - array_stack_size(&dd->front)));
    }
}

/*
要素をセット。
*/
char *darray_deque_set(darray_deque *dd, int offset, char *element)
{
    if (offset < array_stack_size(&dd->front))
    {
        return array_stack_set(&dd->front, (array_stack_size(&dd->front) - offset - 1), element);
    }
    else
    {
        return array_stack_set(&dd->back, (offset - array_stack_size(&dd->front)), element);
    }
}

/*
要素の追加。
*/
int darray_deque_add(darray_deque *dd, int offset, char *element)
{
    int is_added;

    if (offset <= array_stack_size(&dd->front))
    {
        is_added =  array_stack_add(&dd->front, (array_stack_size(&dd->front) - offset), element);
    }
    else
    {
        is_added = array_stack_add(&dd->back, offset - array_stack_size(&dd->front), element);
    }

    darray_deque_balance(dd);

    return is_added;
}

/*
前の配列の末尾に追加。
*/
int darray_deque_fpush(darray_deque *dd, char *element)
{
    return darray_deque_add(dd, array_stack_size(&dd->front), element);
}

/*
後ろの配列の末尾に追加。
*/
int darray_deque_bpush(darray_deque *dd, char *element)
{
    return darray_deque_add(dd, array_stack_size(&dd->back), element);
}

/*
要素の削除。
*/
char *darray_deque_remove(darray_deque *dd, int offset)
{
    char *element;

    if (offset < array_stack_size(&dd->front))
    {
        element = array_stack_remove(&dd->front, (array_stack_size(&dd->front) - offset - 1));
    }
    else
    {
        element = array_stack_remove(&dd->back, (offset - array_stack_size(&dd->front)));
    }

    darray_deque_balance(dd);

    return element;
}

/*
前の配列の末尾を取得。
*/
char *darray_deque_fpop(darray_deque *dd)
{
    return darray_deque_remove(dd, array_stack_size(&dd->front) - 1);
}

/*
後ろの配列の末尾を取得。」
*/
char *darray_deque_bpop(darray_deque *dd)
{
    return darray_deque_remove(dd, array_stack_size(&dd->back) - 1);
}

/*
前と後ろの配列に格納されている要素の数のバランスをとる。
*/
void darray_deque_balance(darray_deque *dd)
{
    int front_size = array_stack_size(&dd->front);
    int back_size = array_stack_size(&dd->back);
    char *element;

    if (front_size - back_size >= 2)
    {
        element = array_stack_remove(&dd->front, 0);
        array_stack_add(&dd->back, 0, element);
    }
    else if (front_size - back_size <= -2)
    {
        element = array_stack_remove(&dd->back, 0);
        array_stack_add(&dd->front, 0, element);
    }
}

/*
dual array dequeの要素を全て表示。
*/
void darray_deque_show(darray_deque *dd)
{
    int i;

    printf("<<<show dual array deque elements>>>\n");
    for (i = array_stack_size(&dd->front) - 1; i >= 0; i--)
    {
        printf("element: %s (front_size = %d, back_size = %d)\n", dd->front.array[i], array_stack_size(&dd->front), array_stack_size(&dd->back));
    }

    for (i = 0; i < array_stack_size(&dd->back); i++)
    {
        printf("element: %s (front_size = %d, back_size = %d)\n", dd->back.array[i], array_stack_size(&dd->front), array_stack_size(&dd->back));
    }

    printf("\n");
}


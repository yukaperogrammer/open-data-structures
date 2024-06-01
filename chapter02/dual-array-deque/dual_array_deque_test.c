#include <stdio.h>
#include "dual_array_deque.h"

int main(int argc, char *argv[])
{
    darray_deque dd;

    printf("init dual array deque\n");
    darray_deque_init(&dd, 3);
    printf("dual array deque size = %d\n", darray_deque_size(&dd));
    printf("dual array duque length = %d\n", dd.front.length + dd.back.length);

    printf("add a\n");
    darray_deque_add(&dd, 0, "a");
    printf("add b\n");
    darray_deque_add(&dd, 1, "b");
    printf("add c\n");
    darray_deque_add(&dd, 2, "c");
    printf("add d\n");
    darray_deque_add(&dd, 3, "d");
    printf("add e\n");
    darray_deque_add(&dd, 4, "e");
    printf("dual array deque size = %d\n", darray_deque_size(&dd));
    printf("dual array duque length = %d\n", dd.front.length + dd.back.length);
    darray_deque_show(&dd);

    printf("add A\n");
    darray_deque_add(&dd, 5, "A");
    printf("add B\n");
    darray_deque_add(&dd, 6, "B");
    printf("add C\n");
    darray_deque_add(&dd, 7, "C");
    printf("add D\n");
    darray_deque_add(&dd, 8, "D");
    printf("dual array deque size = %d\n", darray_deque_size(&dd));
    printf("dual array duque length = %d\n", dd.front.length + dd.back.length);
    darray_deque_show(&dd);

    int i;
    for (i = 0; i < 7; i++)
    {
        printf("fpop\n");
        darray_deque_fpop(&dd);
    }
    printf("dual array deque size = %d\n", darray_deque_size(&dd));
    printf("dual array duque length = %d\n", dd.front.length + dd.back.length);
    darray_deque_show(&dd);

    darray_deque_free(&dd);

    return 0;
}


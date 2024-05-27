#include <stdio.h>
#include "array_deque.h"

int main(int argc, char *argv[])
{
    array_deque ad;

    printf("init array deque\n");
    array_deque_init(&ad, 8);

    printf("add a\n");
    array_deque_add(&ad, 0, "a");
    printf("add b\n");
    array_deque_add(&ad, 1, "b");
    printf("add c\n");
    array_deque_add(&ad, 2, "c");
    printf("add d\n");
    array_deque_add(&ad, 3, "d");
    printf("add e\n");
    array_deque_add(&ad, 4, "e");
    printf("add f\n");
    array_deque_add(&ad, 5, "f");
    printf("add G\n");
    array_deque_add(&ad, 6, "G");
    printf("add H\n");
    array_deque_add(&ad, 7, "H");
    printf("add I\n");
    array_deque_add(&ad, 8, "I");
    printf("array deque size = %d\n", array_deque_size(&ad));
    array_deque_show(&ad);

    printf("remove element of offset 0\n");
    array_deque_remove(&ad, 0);
    printf("array deque size = %d\n", array_deque_size(&ad));
    array_deque_show(&ad);

    printf("remove element of offset 1\n");
    array_deque_remove(&ad, 1);
    printf("array deque size = %d\n", array_deque_size(&ad));
    array_deque_show(&ad);

    printf("remove element of offset 2\n");
    array_deque_remove(&ad, 2);
    printf("array deque size = %d\n", array_deque_size(&ad));
    array_deque_show(&ad);

    printf("remove element of offset 4\n");
    array_deque_remove(&ad, 4);
    printf("array deque size = %d\n", array_deque_size(&ad));
    array_deque_show(&ad);

    printf("get element of offset 2\n");
    printf("element of offset 2 = %s\n", array_deque_get(&ad, 2));
    printf("array deque size = %d\n", array_deque_size(&ad));
    array_deque_show(&ad);

    printf("set XXX offset 2\n");
    array_deque_set(&ad, 2, "XXX");
    printf("array deque size = %d\n", array_deque_size(&ad));
    array_deque_show(&ad);

    array_deque_free(&ad);

    return 0;
}


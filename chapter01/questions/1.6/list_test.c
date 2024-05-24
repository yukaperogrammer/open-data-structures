/* 問1.5 */
#include <stdio.h>
#include "list.h"

int main(int argc, char *argv[])
{
    list alpha_l;
    char *cp;

    printf("init list\n");
    list_init(&alpha_l);

    printf("add a to offset 0\n");
    list_add(&alpha_l, 0, "a");
    printf("add b to offset 1\n");
    list_add(&alpha_l, 1, "b");
    printf("add c to offset 2\n");
    list_add(&alpha_l, 2, "c");
    printf("add d to offset 3\n");
    list_add(&alpha_l, 3, "d");
    printf("add e to offset 4\n");
    list_add(&alpha_l, 4, "e");
    printf("add f to offset 5\n");
    list_add(&alpha_l, 5, "f");
    printf("add g to offset 6\n");
    list_add(&alpha_l, 6, "g");
    printf("list size = %d\n", list_size(&alpha_l));
    list_show(&alpha_l);

    printf("set A to offset 0\n");
    list_set(&alpha_l, 0, "A");
    printf("set E to offset 4\n");
    list_set(&alpha_l, 4, "E");
    printf("list size = %d\n", list_size(&alpha_l));
    list_show(&alpha_l);

    printf("add H to offset 4\n");
    list_add(&alpha_l, 4, "H");
    printf("list size = %d\n", list_size(&alpha_l));
    list_show(&alpha_l);

    printf("add X to offset 100\n");
    list_add(&alpha_l, 100, "X");
    printf("set Y to offset 100\n");
    list_set(&alpha_l, 100, "Y");
    printf("list size = %d\n", list_size(&alpha_l));
    list_show(&alpha_l);

    printf("get element of offset 3\n");
    cp = list_get(&alpha_l, 3);
    if (cp != NULL)
    {
        printf("element is %s of offset 3\n", cp);
    }
    else
    {
        printf("offset out of range\n");
    }

    printf("get element of offset 10\n");
    cp = list_get(&alpha_l, 10);
    if (cp != NULL)
    {
        printf("element is %s of offset 10\n", cp);
    }
    else
    {
        printf("offset out of range\n");
    }
    printf("list size = %d\n", list_size(&alpha_l));
    list_show(&alpha_l);

    printf("add FIRST to offset 0\n");
    list_add(&alpha_l, 0, "FIRST");
    printf("add LAST to offset %d\n", list_size(&alpha_l));
    list_add(&alpha_l, list_size(&alpha_l), "LAST");
    printf("list size = %d\n", list_size(&alpha_l));
    list_show(&alpha_l);

    list_free(&alpha_l);

    return 0;
}


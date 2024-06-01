#include <stdio.h>
#include "array_stack.h"

int main(int argc, char *argv[])
{
    char *tmp;
    array_stack as;

    printf("init array stack\n");
    array_stack_init(&as, 2);
    printf("array stack length = %d\n", as.length);

    printf("add aa\n");
    array_stack_add(&as, 0, "aa");
    printf("add bb\n");
    array_stack_add(&as, 1, "bb");
    printf("add cc\n");
    array_stack_add(&as, 2, "cc");
    printf("add dd\n");
    array_stack_add(&as, 3, "dd");
    printf("add ee\n");
    array_stack_add(&as, 4, "ee");
    printf("add ff\n");
    array_stack_add(&as, 5, "ff");
    printf("array stack size = %d\n", array_stack_size(&as));
    printf("array stack length = %d\n", as.length);
    array_stack_show(&as);

    printf("remove element of 0 offset\n");
    array_stack_remove(&as, 0);
    printf("remove element of 0 offset\n");
    array_stack_remove(&as, 0);
    printf("remove element of 0 offset\n");
    array_stack_remove(&as, 0);
    printf("remove element of 0 offset\n");
    array_stack_remove(&as, 0);
    printf("array stack size = %d\n", array_stack_size(&as));
    printf("array stack length = %d\n", as.length);
    array_stack_show(&as);

    printf("remove element of 3 offset\n");
    array_stack_remove(&as, 3);
    printf("array stack size = %d\n", array_stack_size(&as));
    printf("array stack length = %d\n", as.length);
    array_stack_show(&as);

    printf("1 offset element to AA\n");
    array_stack_set(&as, 1, "AA");
    printf("array stack size = %d\n", array_stack_size(&as));
    printf("array stack length = %d\n", as.length);
    array_stack_show(&as);

    printf("get element of 1 offset\n");
    tmp = array_stack_get(&as, 1);
    if (tmp != NULL)
    {
        printf("get element %s\n", tmp);
    }
    else
    {
        printf("can not get element\n");
    }
    printf("get element of 3 offset\n");
    tmp = array_stack_get(&as, 3);
    if (tmp != NULL)
    {
        printf("get element %s\n", tmp);
    }
    else
    {
        printf("can not get element\n");
    }
    printf("array stack size = %d\n", array_stack_size(&as));
    printf("array stack length = %d\n", as.length);
    array_stack_show(&as);

    printf("add A\n");
    array_stack_add(&as, 0, "A");
    printf("add B\n");
    array_stack_add(&as, 0, "B");
    printf("add C\n");
    array_stack_add(&as, 0, "C");
    printf("add D\n");
    array_stack_add(&as, 0, "D");
    printf("add E\n");
    array_stack_add(&as, 0, "E");
    printf("add F\n");
    array_stack_add(&as, 0, "F");
    printf("add G\n");
    array_stack_add(&as, 0, "G");
    printf("add H\n");
    array_stack_add(&as, 0, "H");
    printf("add I\n");
    array_stack_add(&as, 0, "I");
    printf("array stack size = %d\n", array_stack_size(&as));
    printf("array stack length = %d\n", as.length);
    array_stack_show(&as);

    array_stack_free(&as);

    return 0;
}


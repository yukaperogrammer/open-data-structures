#include <stdio.h>
#include "uset_err.h"

int main(int argc, char *argv[])
{
    init_uset();
    printf("add a\n");
    add("a");
    printf("add b\n");
    add("b");
    printf("add c\n");
    add("c");
    printf("add d\n");
    add("d");
    printf("add e\n");
    add("e");
    printf("add f\n");
    add("f");
    printf("uset size = %d\n", size());
    show_uset();

    printf("find d\n");
    printf("element = %s\n", find("d"));

    printf("remove d\n");
    remv("d");
    printf("uset size = %d\n", size());
    show_uset();

    printf("remove a(first elements)\n");
    remv("a");
    printf("uset size = %d\n", size());
    show_uset();

    printf("remove f(last elements)\n");
    remv("f");
    printf("uset size = %d\n", size());
    show_uset();

    printf("add g\n");
    add("g");
    printf("uset size = %d\n", size());
    show_uset();

    printf("add g\n");
    add("g");
    printf("uset size = %d\n", size());
    show_uset();

    all_free();

    return 0;
}


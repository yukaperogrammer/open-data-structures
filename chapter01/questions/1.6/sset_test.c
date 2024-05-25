/* 問1.6 */
#include <stdio.h>
#include "sset.h"

int main(int argc, char *argv[])
{
    sset sset_al;
    printf("init sset\n");
    sset_init(&sset_al);

    printf("add f\n");
    sset_add(&sset_al, "f");
    printf("add b\n");
    sset_add(&sset_al, "b");
    printf("add a\n");
    sset_add(&sset_al, "a");
    printf("add d\n");
    sset_add(&sset_al, "d");
    printf("add e\n");
    sset_add(&sset_al, "e");
    printf("add c\n");
    sset_add(&sset_al, "c");
    printf("add g\n");
    sset_add(&sset_al, "g");
    printf("sset size = %d\n", sset_size(&sset_al));
    sset_show(&sset_al);

    printf("remove a\n");
    sset_remove(&sset_al, "a");
    printf("remove g\n");
    sset_remove(&sset_al, "g");
    printf("sset size = %d\n", sset_size(&sset_al));
    sset_show(&sset_al);

    printf("find b\n");
    printf("result = %s\n", sset_find(&sset_al, "b"));
    printf("find e\n");
    printf("result = %s\n", sset_find(&sset_al, "e"));
    printf("\n");

    printf("add v\n");
    sset_add(&sset_al, "v");
    printf("add x\n");
    sset_add(&sset_al, "x");
    printf("add z\n");
    sset_add(&sset_al, "z");
    printf("sset size = %d\n", sset_size(&sset_al));
    sset_show(&sset_al);

    printf("find o\n");
    printf("result = %s\n", sset_find(&sset_al, "o"));
    printf("find x\n");
    printf("result = %s\n", sset_find(&sset_al, "x"));
    printf("find y\n");
    printf("result = %s\n", sset_find(&sset_al, "y"));
    printf("\n");

    printf("sset size = %d\n", sset_size(&sset_al));
    sset_show(&sset_al);

    sset_free(&sset_al);

    return 0;
}


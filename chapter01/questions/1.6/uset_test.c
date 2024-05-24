/* 問1.5 */
#include <stdio.h>
#include "uset.h"

int main(int argc, char *argv[])
{
    uset uset_alpha;

    printf("initialize\n");
    uset_init(&uset_alpha);

    printf("add a\n");
    uset_add(&uset_alpha, "a");
    printf("add b\n");
    uset_add(&uset_alpha, "b");
    printf("add c\n");
    uset_add(&uset_alpha, "c");
    printf("add d\n");
    uset_add(&uset_alpha, "d");
    printf("add e\n");
    uset_add(&uset_alpha, "e");
    printf("add f\n");
    uset_add(&uset_alpha, "f");
    printf("add g\n");
    uset_add(&uset_alpha, "g");
    printf("add h\n");
    uset_add(&uset_alpha, "h");
    printf("add i\n");
    uset_add(&uset_alpha, "i");
    printf("add j\n");
    uset_add(&uset_alpha, "j");
    printf("add k\n");
    uset_add(&uset_alpha, "k");
    printf("uset size = %d\n", uset_size(&uset_alpha));
    uset_show_elements(&uset_alpha);

    printf("remove e\n");
    uset_remove(&uset_alpha, "e");
    printf("remove a\n");
    uset_remove(&uset_alpha, "a");
    printf("remove i\n");
    uset_remove(&uset_alpha, "i");
    printf("uset size = %d\n", uset_size(&uset_alpha));
    uset_show_elements(&uset_alpha);

    printf("add A\n");
    uset_add(&uset_alpha, "A");
    printf("add Z\n");
    uset_add(&uset_alpha, "Z");
    printf("uset size = %d\n", uset_size(&uset_alpha));
    uset_show_elements(&uset_alpha);

    printf("find f\n");
    if (uset_find(&uset_alpha, "f") != NULL)
    {
        printf("f is found\n");
    }
    else
    {
        printf("f is not found\n");
    }

    printf("find M\n");
    if (uset_find(&uset_alpha, "M") != NULL)
    {
        printf("M is found\n");
    }
    else
    {
        printf("M is not found\n");
    }

    uset_all_free(&uset_alpha);
    return 0;
}


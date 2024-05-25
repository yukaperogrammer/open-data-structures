#include <stdio.h>
#include "bag.h"

int main(int argc, char *argv[])
{
    bag bag_al;
    char array[][MAX_STRING_SIZE] = {
        "a",
        "b",
        "g",
        "d",
        "e"
    };
    int arr_size = sizeof(array) / sizeof(array[0]);
    char *cp;
    uset_node *ptr;

    printf("init bag\n");
    bag_init(&bag_al);

    printf("add a\n");
    bag_add(&bag_al, "a");
    printf("add b\n");
    bag_add(&bag_al, "b");
    printf("add c\n");
    bag_add(&bag_al, "c");
    printf("add d\n");
    bag_add(&bag_al, "d");
    printf("add e\n");
    bag_add(&bag_al, "e");
    printf("add f\n");
    bag_add(&bag_al, "f");
    printf("add g\n");
    bag_add(&bag_al, "g");
    printf("bag size = %d\n", bag_size(&bag_al));
    bag_show_elements(&bag_al);

    printf("find all (a, b, g, d, e)\n");
    printf("<<<show list>>>\n");
    for (ptr = bag_find_all(&bag_al, array, arr_size); ptr != NULL; ptr = ptr->next)
    {
        printf("%s\n", ptr->key);
    }
    printf("\n");

    printf("add a\n");
    bag_add(&bag_al, "a");
    printf("add b\n");
    bag_add(&bag_al, "b");
    printf("bag size = %d\n", bag_size(&bag_al));
    bag_show_elements(&bag_al);

    printf("remove c\n");
    bag_remove(&bag_al, "c");
    printf("remove d\n");
    bag_remove(&bag_al, "d");
    printf("remove e\n");
    bag_remove(&bag_al, "e");
    printf("bag size = %d\n", bag_size(&bag_al));
    bag_show_elements(&bag_al);

    printf("find a\n");
    if ((cp = bag_find(&bag_al, "a")) != NULL)
    {
        printf("a is found\n");
    }
    else
    {
        printf("a is not found\n");
    }

    printf("find c\n");
    if ((cp = bag_find(&bag_al, "c")) != NULL)
    {
        printf("c is found\n");
    }
    else
    {
        printf("c is not found\n");
    }

    printf("find all (a, b, g, d, e)\n");
    printf("<<<show list>>>\n");
    for (ptr = bag_find_all(&bag_al, array, arr_size); ptr != NULL; ptr = ptr->next)
    {
        printf("%s\n", ptr->key);
    }
    printf("\n");

    bag_all_free(&bag_al);

    return 0;
}


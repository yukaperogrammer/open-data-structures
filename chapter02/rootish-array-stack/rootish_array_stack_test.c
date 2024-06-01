#include <stdio.h>
#include "rootish_array_stack.h"

int main(int argc, char *argv[])
{
    rarray_stack ras;

    printf("init rootish array stack\n");
    rarray_stack_init(&ras);

    printf("push AAA\n");
    rarray_stack_push(&ras, "AAA");
    printf("push BBB\n");
    rarray_stack_push(&ras, "BBB");
    printf("push CCC\n");
    rarray_stack_push(&ras, "CCC");
    printf("num of element = %d\n", ras.num_of_element);
    printf("num of block = %d\n", ras.num_of_block);
    rarray_stack_show(&ras);

    printf("push DDD\n"); 
    rarray_stack_push(&ras, "DDD");
    printf("push EEE\n");
    rarray_stack_push(&ras, "EEE");
    printf("push FFF\n");
    rarray_stack_push(&ras, "FFF");
    printf("push GGG\n");
    rarray_stack_push(&ras, "GGG");
    printf("push HHH\n");
    rarray_stack_push(&ras, "HHH");
    printf("num of element = %d\n", ras.num_of_element);
    printf("num of block = %d\n", ras.num_of_block);
    rarray_stack_show(&ras);

    printf("pop\n");
    printf("result = %s\n", rarray_stack_pop(&ras));
    printf("pop\n");
    printf("result = %s\n", rarray_stack_pop(&ras));
    printf("pop\n");
    printf("result = %s\n", rarray_stack_pop(&ras));
    printf("pop\n");
    printf("result = %s\n", rarray_stack_pop(&ras));
    printf("pop\n");
    printf("result = %s\n", rarray_stack_pop(&ras));
    printf("num of element = %d\n", ras.num_of_element);
    printf("num of block = %d\n", ras.num_of_block);
    rarray_stack_show(&ras);

    rarray_stack_free(&ras);

    return 0;
}


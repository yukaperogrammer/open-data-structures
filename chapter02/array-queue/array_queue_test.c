#include <stdio.h>
#include "array_queue.h"

int main(int argc, char *argv[])
{
    array_queue aq;

    printf("init array queue (size = 8)\n");
    array_queue_init(&aq, 8);

    printf("add a\n");
    array_queue_add(&aq, "a");
    printf("add b\n");
    array_queue_add(&aq, "b");
    printf("add c\n");
    array_queue_add(&aq, "c");
    printf("add d\n");
    array_queue_add(&aq, "d");
    printf("add e\n");
    array_queue_add(&aq, "e");
    printf("add f\n");
    array_queue_add(&aq, "f");
    printf("array queue size = %d\n", array_queue_size(&aq));
    printf("array queue length = %d\n", aq.length);
    array_queue_show(&aq);

    printf("remove\n");
    array_queue_remove(&aq);
    printf("remove\n");
    array_queue_remove(&aq);
    printf("array queue size = %d\n", array_queue_size(&aq));
    printf("array queue length = %d\n", aq.length);
    array_queue_show(&aq);

    printf("add A\n");
    array_queue_add(&aq, "A");
    printf("add B\n");
    array_queue_add(&aq, "B");
    printf("add C\n");
    array_queue_add(&aq, "C");
    printf("add D\n");
    array_queue_add(&aq, "D");
    printf("add E\n");
    array_queue_add(&aq, "E");
    printf("add F\n");
    array_queue_add(&aq, "F");
    printf("array queue size = %d\n", array_queue_size(&aq));
    printf("array queue length = %d\n", aq.length);
    array_queue_show(&aq);

    printf("remove\n");
    array_queue_remove(&aq);
    printf("remove\n");
    array_queue_remove(&aq);
    printf("array queue size = %d\n", array_queue_size(&aq));
    printf("array queue length = %d\n", aq.length);
    array_queue_show(&aq);

    printf("add XX\n");
    array_queue_add(&aq, "XX");
    printf("add YY\n");
    array_queue_add(&aq, "YY");
    printf("array queue size = %d\n", array_queue_size(&aq));
    printf("array queue length = %d\n", aq.length);
    array_queue_show(&aq);

    printf("remove\n");
    array_queue_remove(&aq);
    printf("remove\n");
    array_queue_remove(&aq);
    printf("remove\n");
    array_queue_remove(&aq);
    printf("remove\n");
    array_queue_remove(&aq);
    printf("remove\n");
    array_queue_remove(&aq);
    printf("remove\n");
    array_queue_remove(&aq);
    printf("remove\n");
    array_queue_remove(&aq);
    printf("remove\n");
    array_queue_remove(&aq);
    printf("remove\n");
    array_queue_remove(&aq);
    printf("remove\n");
    array_queue_remove(&aq);
    printf("array queue size = %d\n", array_queue_size(&aq));
    printf("array queue length = %d\n", aq.length);
    array_queue_show(&aq);


    printf("add 100\n");
    array_queue_add(&aq, "100");
    printf("add 200\n");
    array_queue_add(&aq, "200");
    printf("array queue size = %d\n", array_queue_size(&aq));
    printf("array queue length = %d\n", aq.length);
    array_queue_show(&aq);

    printf("add 300\n");
    array_queue_add(&aq, "300");
    printf("array queue size = %d\n", array_queue_size(&aq));
    printf("array queue length = %d\n", aq.length);
    array_queue_show(&aq);

    array_queue_free(&aq);

    return 0;
}


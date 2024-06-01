#ifndef ARRAY_STACK_H
#define ARRAY_STACK_H

#include "backing_array.h"

typedef struct array_stack {
    backing_array barr;
    int num_of_element; /* 配列に格納されている要素の数（常に num_of_element <= barr.length ） */
} array_stack;

void array_stack_init(array_stack *, int);
int array_stack_size(array_stack *);
char *array_stack_get(array_stack *, int);
char *array_stack_set(array_stack *, int, char *);
int array_stack_add(array_stack *, int, char *);
char *array_stack_remove(array_stack *, int);
int array_stack_resize(array_stack *);
void array_stack_free(array_stack *);
void array_stack_show(array_stack *);

#endif


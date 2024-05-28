#ifndef ARRAY_STACK_H
#define ARRAY_STACK_H

typedef struct array_stack {
    char **array;
    int length;
    int num_of_element;
} array_stack;

int array_stack_init(array_stack *, int);
void array_stack_free(array_stack *);
int array_stack_size(array_stack *);
char *array_stack_get(array_stack *, int);
char *array_stack_set(array_stack *, int, char *);
int array_stack_add(array_stack *, int, char *);
int array_stack_push(array_stack *, char *);
char *array_stack_remove(array_stack *, int);
char *array_stack_pop(array_stack *);
void array_stack_show(array_stack *);
int is_empty(array_stack *);
int is_full(array_stack *);
int array_stack_resize(array_stack *);
void *xmalloc(void *, int);

#endif


#ifndef ROOTISH_ARRAY_STACK_H
#define ROOTISH_ARRAY_STACK_H

typedef struct block {
    char **array;
    int length;
} block;

typedef struct rarray_stack {
    struct block **blocks;
    int num_of_element;
    int num_of_block;
    int next_block_length;
} rarray_stack;

int rarray_stack_init(rarray_stack *);
void rarray_stack_free(rarray_stack *);
char *rarray_stack_get(rarray_stack *, int);
char *rarray_stack_set(rarray_stack *, int, char *);
int rarray_stack_add(rarray_stack *, int, char *);
int rarray_stack_push(rarray_stack *, char *);
char *rarray_stack_remove(rarray_stack *, int);
char *rarray_stack_pop(rarray_stack *);
void rarray_stack_show(rarray_stack *);
int offset_to_boffset(int);
int grow(rarray_stack *);
int shrink(rarray_stack *);
int is_empty(rarray_stack *);
int is_full(rarray_stack *);
void *xmalloc(void *, int);

#endif


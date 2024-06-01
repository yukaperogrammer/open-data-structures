#ifndef DUAL_ARRAY_DEQUE_H
#define DUAL_ARRAY_DEQUE_H

#include "array_stack.h"

typedef struct darray_deque {
    array_stack front;
    array_stack back;
} darray_deque;

int darray_deque_init(darray_deque *, int);
void darray_deque_free(darray_deque *);
int darray_deque_size(darray_deque *);
char *darray_deque_get(darray_deque *, int);
char *darray_deque_set(darray_deque *, int, char *); 
int darray_deque_add(darray_deque *, int, char *);
int darray_deque_fpush(darray_deque *, char *);
int darray_deque_bpufh(darray_deque *, char *);
char *darray_deque_remove(darray_deque *, int);
char *darray_deque_fpop(darray_deque *);
char *darray_deque_bpop(darray_deque *);
void darray_deque_balance(darray_deque *);
void darray_deque_show(darray_deque *);

#endif


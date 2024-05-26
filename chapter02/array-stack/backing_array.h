#ifndef BACKING_ARRAY_H
#define BACKING_ARRAY_H

typedef struct backing_array {
    char **array;
    int length;         /* 配列の大きさ */
} backing_array;

int backing_array_init(backing_array *, int);
void backing_array_free(backing_array *);
void *xmalloc(void *, int);

#endif


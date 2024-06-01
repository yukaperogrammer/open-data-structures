#ifndef ARRAY_DEQUE_H
#define ARRAY_DEQUE_H

typedef struct array_deque {
    char **array;       /* リングバッファ */
    int length;         /* 配列の大きさ */
    int num_of_element; /* 配列に格納されている要素の数 */
    int head;           /* 先頭のインデックス */
    int tail;           /* 末尾のインデックス */
} array_deque;

int array_deque_init(array_deque *, int);
void array_deque_free(array_deque *);
int array_deque_size(array_deque *);
char *array_deque_get(array_deque *, int);
char *array_deque_set(array_deque *, int, char *);
int array_deque_add(array_deque *, int, char *);
char *array_deque_remove(array_deque *, int);
void array_deque_show(array_deque *);
int is_empty(array_deque *);
int is_full(array_deque *);
int mod(int, int);
void *xmalloc(void *, int);

#endif


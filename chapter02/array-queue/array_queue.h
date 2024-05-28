#ifndef ARRAY_QUEUE_H
#define ARRAY_QUEUE_H

typedef struct array_queue {
    char **array;       /* リングバッファとして使う */
    int length;         /* 配列の大きさ */
    int head;           /* 先頭のインデックス */
    int tail;           /* 末尾のインデックス */
    int num_of_element; /* 配列に格納されている要素の個数 */
} array_queue;

int array_queue_init(array_queue *, int);
void array_queue_free(array_queue *);
int array_queue_size(array_queue *);
int array_queue_add(array_queue *, char *);
char *array_queue_remove(array_queue *);
int is_empty(array_queue *);
int is_full(array_queue *);
void array_queue_show(array_queue *);
int array_queue_resize(array_queue *);
void *xmalloc(void *, int);

#endif


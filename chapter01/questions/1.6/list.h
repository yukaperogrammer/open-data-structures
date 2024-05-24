/* 問1.5 */
#ifndef LIST_H
#define LIST_H

typedef struct node {
    char *value;
    struct node *next;
} node;

typedef struct list {
    struct node *head;
    int num_of_node;
} list;

void list_init(list *);
int list_size(list *);
char *list_get(list *, int);
int list_set(list *, int, char *);
int list_add(list *, int, char *);
int list_remove(list *, int);
void list_show(list *);
void list_free(list *);
void *xmalloc(void *, int);

#endif


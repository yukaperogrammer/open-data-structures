/* 問1.6 */
#ifndef SSET_H
#define SSET_H

typedef struct node {
    char *value;
    struct node *next;
} node;

typedef struct sset {
    struct node *head;
    int num_of_node;
} sset;

void sset_init(sset *);
void sset_free(sset *);
int sset_size(sset *);
int sset_add(sset *, char *);
char *sset_remove(sset *, char *);
char *sset_find(sset *, char *);
void sset_show(sset *);
void *xmalloc(void *, int);

#endif


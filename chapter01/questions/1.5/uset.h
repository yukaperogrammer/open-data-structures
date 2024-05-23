#ifndef USET_H
#define USET_H

#define TABLE_SIZE 100

typedef struct uset_node {
    char *key;
    struct uset_node *next;
} uset_node;

typedef struct uset {
    uset_node *hashtable[TABLE_SIZE];
    int num_of_node;
} uset;

void uset_init(uset *);
int uset_size(uset *);
int uset_add(uset *, char *);
char *uset_remove(uset *, char *);
char *uset_find(uset *, char *);
unsigned int hash(char *);
void *xmalloc(void *, int); 
void uset_all_free(uset *);
void uset_show_elements(uset *);

#endif


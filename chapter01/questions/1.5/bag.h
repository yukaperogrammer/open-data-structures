#include "uset.h"

#ifndef BAG_H
#define BAG_H

#define MAX_STRING_SIZE 64

typedef struct bag {
    uset interface;
} bag;

void bag_init(bag *);
void bag_all_free(bag *);
int bag_size(bag *);
int bag_add(bag *, char *);
char *bag_remove(bag *, char *);
char *bag_find(bag *, char *);
uset_node *bag_find_all(bag *, char (*)[], int);
int is_not_contains(char *, char (*)[], int);
void list_free(uset_node *);
void bag_show_elements(bag *);

#endif


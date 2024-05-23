#ifndef USET_H
#define USET_H

#define MAX_STRING_SIZE 32

/* usetの要素は文字列で表す */
typedef struct uset_t {
    char element[MAX_STRING_SIZE];
    struct uset_t *next;
} uset;

void init_uset(void);
int size(void);
int add(char *);
char *remv(char *);
char *find(char *);
void show_uset(void);
void *xmalloc(void *, int);
void all_free(void);

#endif


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "uset.h"

#define TRUE 1
#define FALSE 0

/*
usetを初期化する。
*/
void uset_init(uset *usetp)
{
    int i;

    /* hashtableの先頭全てにNULLを代入する */
    for (i = 0; i < TABLE_SIZE; i++)
    {
        usetp->hashtable[i] = NULL;
    }

    usetp->num_of_node = 0;

    return;
}

/* usetのサイズ（要素の数）を返す。 */
int uset_size(uset *usetp)
{
    return usetp->num_of_node;
}

/*
usetに要素を追加する。
要素を追加できればTRUE、追加できなければFALSEを返す。
*/
int uset_add(uset *usetp, char *key)
{
    uset_node *current, *prev, *p;
    unsigned int hashval;

    hashval = hash(key);
    prev = NULL;

    /* 重複を調べる */
    for (current = usetp->hashtable[hashval]; current != NULL; current = current->next)
    {
        if (strcmp(current->key, key) == 0)
        {
            /* すでに存在していて追加できないのでFALSE */
            return FALSE;
        }

        prev = current;
    }

    p = (uset_node *)xmalloc(NULL, sizeof(uset_node));
    if (p == NULL)
    {
        /* メモリ確保の失敗で追加できないのでFALSE */
        return FALSE;
    }
    p->key = key;
    p->next = NULL;

    if (prev == NULL)
    {
        /* prev == NULL ならば要素がないので先頭に追加 */
        usetp->hashtable[hashval] = p;
    }
    else
    {
        /* prev != NULL ならば末尾に追加 */
        prev->next = p;
    }

    /* 要素が1つ増えたのでサイズを増やす */
    usetp->num_of_node++;

    return TRUE;
}

/*
usetから要素を削除する。
削除対象要素があればその要素を、存在しなければNULLを返す。
*/
char *uset_remove(uset *usetp, char *key)
{
    uset_node *current, *prev;
    unsigned int hashval;

    hashval = hash(key);
    prev = NULL;

    for (current = usetp->hashtable[hashval]; current != NULL; current = current->next)
    {
        if (strcmp(current->key, key) == 0)
        {
            if (prev == NULL)
            {
                /* 先頭の場合 */
                /* 先頭に1つ後のノードを繋げる */
                usetp->hashtable[hashval] = current->next;
            }
            else
            {
                /* 先頭以外の場合 */
                /* 1つ前のノードに1つ後のノードを繋げる */
                prev->next = current->next;
            }

            free(current);
            usetp->num_of_node--;

            return key;
        }

        prev = current;
    }

    return NULL;
}

/*
usetから要素を探す。
見つかればその要素を、存在しなければNULLを返す。
*/
char *uset_find(uset *usetp, char *key)
{
    uset_node *current;
    unsigned int hashval;

    hashval = hash(key);

    for (current = usetp->hashtable[hashval]; current != NULL; current = current->next)
    {
        if (strcmp(current->key, key) == 0)
        {
            return key;
        }
    }

    return NULL;
}

/*
引数に与えられた文字列に対してhash値を生成して返す。
*/
unsigned int hash(char *key)
{
    unsigned int hash;
    
    for (hash = 0; *key; key++)
    {
        hash = (hash << 5) + *key;
    }

    return hash % TABLE_SIZE;
}

/*
メモリの動的確保を行う。
ptr == NULL ならばsizeバイト確保。
ptr != NULL ならばptrをsizeバイトに拡張/縮小。
*/
void *xmalloc(void *ptr, int size)
{
    void *p;

    if (ptr == NULL)
    {
        p = malloc(size);
    }
    else
    {
        p = realloc(ptr, size);
    }

    return p;
}

/*
usetを全て開放する。
*/
void uset_all_free(uset *usetp)
{
    uset_node *current, *next;
    int i;

    for (i = 0; i < TABLE_SIZE; i++)
    {
        for (current = usetp->hashtable[i], next = NULL; current != NULL; current = next)
        {
            next = current->next;
            free(current);
        }
    }

    return;
}

void uset_show_elements(uset *usetp)
{
    uset_node *current;
    int i;

    printf("<<<show uset elements>>>\n");
    for (i = 0; i < TABLE_SIZE; i++)
    {
        for (current = usetp->hashtable[i]; current != NULL; current = current->next)
        {
            printf("element: %s\n", current->key);
        }
    }
    printf("\n");
}


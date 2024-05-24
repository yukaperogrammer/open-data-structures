#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bag.h"

#define TRUE 1
#define FALSE 0

/*
bagを初期化する。
*/
void bag_init(bag *bagp)
{
    uset_init(&bagp->interface);
}

/*
bagを全て開放する。
*/
void bag_all_free(bag *bagp)
{
    uset_all_free(&bagp->interface);
}

/*
bagのサイズ（要素数）を返す。
*/
int bag_size(bag *bagp)
{
    return bagp->interface.num_of_node;
}

/*
bagに要素を追加する。
追加できればTRUE、追加できなければFALSEを返す。
*/
int bag_add(bag *bagp, char *key)
{
    uset_node *current, *prev, *p;
    unsigned int hashval;

    hashval = hash(key);

    prev = NULL;
    for (current = bagp->interface.hashtable[hashval]; current != NULL; current = current->next)
    {
        prev = current;
    }

    p = (uset_node *)xmalloc(NULL, sizeof(uset_node));
    if (p == NULL)
    {
        /* メモリの確保に失敗して要素の追加ができないのでFALSE */
        return FALSE;
    }

    p->key = key;
    p->next = NULL;

    if (prev == NULL)
    {
        /* 先頭に追加 */
        bagp->interface.hashtable[hashval] = p;
    }
    else
    {
        /* 末尾に追加 */
        prev->next = p;
    }

    /* 要素が追加されたのでサイズを1増やす */
    bagp->interface.num_of_node++;

    return TRUE;
}

/*
bagから対象要素を1つ削除する。
削除できればその要素を返し、失敗すればNULLを返す。
*/
char *bag_remove(bag *bagp, char *key)
{
    return uset_remove(&bagp->interface, key);
}

/*
bagから対象要素を探す。
存在すればTRUE、存在しなければFALSEを返す。
*/
char *bag_find(bag *bagp, char *key)
{
    return uset_find(&bagp->interface, key);
}

/*
bagから要素の配列に含まれているもののリストを返す。
配列の要素数（num_of_elements）も一緒に渡す。
*/
uset_node *bag_find_all(bag *bagp, char (*key_array)[MAX_STRING_SIZE], int num_of_elements)
{
    uset_node *current, *prev, *head, *tbl_current;
    int i;

    current = NULL;
    head = NULL;
    for (i = 0; i < TABLE_SIZE; i++)
    {
        for (tbl_current = bagp->interface.hashtable[i]; tbl_current != NULL; tbl_current = tbl_current->next)
        {
            if (is_not_contains(tbl_current->key, key_array, num_of_elements))
            {
                /* 含まれていないならリスト作成処理は実行しない */
                continue;
            }

            /* リスト作成 */
            current = (uset_node *)xmalloc(NULL, sizeof(uset_node));
            if (current == NULL)
            {
                /* メモリ確保失敗でリストを返せないのでNULL */
                list_free(head);
                return NULL;
            }
            current->key = tbl_current->key;
            current->next = NULL;

            if (head == NULL)
            {
                head = current;
            }
            else
            {
                prev->next = current;
            }

            prev = current;
        }
    }

    /* リストの先頭要素へのポインタを返す */
    return head;
}

/*
key_array内に要素keyが含まれているか判定する。
含まれていなければTRUE、含まれていればFALSEを返す。
*/
int is_not_contains(char *key, char (*key_array)[MAX_STRING_SIZE], int num_of_elements)
{
    int i;

    for (i = 0; i < num_of_elements; i++)
    {
        if (strcmp(key, key_array[i]) == 0)
        {
            /* 含まれているのでFALSE */
            return FALSE;
        }
    }

    /* 含まれていないのでTRUE */
    return TRUE;
}

/*
headから始まるリストのメモリを開放する。
*/
void list_free(uset_node *head)
{
    uset_node *current, *prev;

    current = head;
    prev = NULL;
    while (current != NULL)
    {
        prev = current;
        current = current->next;
        free(prev);
    }

    return;
}

/*
bagの要素を表示する。
*/
void bag_show_elements(bag *bagp)
{
    uset_node *current;
    int i;

    printf("<<<show bag elements>>>\n");
    for (i = 0; i < TABLE_SIZE; i++)
    {
        for (current = bagp->interface.hashtable[i]; current != NULL; current = current->next)
        {
            printf("element: %s\n", current->key);
        }
    }
    printf("\n");

    return;
}


/* 問1.5 */
#include <stdio.h>
#include <stdlib.h>
#include "list.h"

#define TRUE 1
#define FALSE 0

void list_init(list *listp)
{
    listp->head = NULL;
    listp->num_of_node = 0;
}

int list_size(list *listp)
{
    return listp->num_of_node;
}

char *list_get(list *listp, int offset)
{
    int i;
    node *target;

    if (offset >= listp->num_of_node)
    {
        /* ノード数以上のインデックスの要素は存在しないのでNULL */
        return NULL;
    }

    target = listp->head;
    for (i = 0; i < offset; i++)
    {
        target = target->next;
    }

    return target->value;
}

int list_set(list *listp, int offset, char *value)
{
    int i;
    node *target; 

    if (offset >= listp->num_of_node)
    {
        /* ノード数以上のインデックスの要素は存在しないのでFALSE */
        return FALSE;
    }

    target = listp->head;
    for (i = 0; i < offset; i++)
    {
        target = target->next;
    }

    /* offsetインデックスのノードの値を変更 */
    target->value = value;

    return TRUE;
}

int list_add(list *listp, int offset, char *value)
{
    int i;
    node *current, *prev, *new;

    if (offset > listp->num_of_node)
    {
        /* ノード数より大きいインデックスは無効 */
        /* 末尾に追加するときだけoffset == num_of_node */
        return FALSE;
    }

    prev = NULL;
    current = listp->head;
    for (i = 0; i < offset; i++)
    {
        prev = current;
        current = current->next;
    }

    new = (node *)xmalloc(NULL, sizeof(node));
    if (new == NULL)
    {
        /* メモリの確保エラーで追加できないのでFALSE */
        return FALSE;
    }

    new->value = value;
    new->next = current;
    if (prev == NULL)
    {
        /* 先頭に追加 */
        listp->head = new;
    }
    else
    {
        /* 先頭以外に追加 */
        prev->next = new;
        new->next = current;
    }

    /* ノードが1つ増えたのでサイズを増やす */
    listp->num_of_node++;

    return TRUE;
}

int list_remove(list *listp, int offset)
{
    int i;
    node *target, *prev;

    if (offset >= listp->num_of_node)
    {
        /* ノード数以上のインデックスの要素は存在しないのでFALSE */
        return FALSE;
    }

    prev = NULL;
    target = listp->head;
    for (i = 0; i < offset; i++)
    {
        prev = target;
        target = target->next;
    }

    if (prev == NULL)
    {
        /* 先頭の削除 */
        listp->head = target->next;
    }
    else
    {
        /* 先頭以外の削除（末尾の削除も含まれる） */
        prev->next = target->next;
    }

    /* offset番目のノードを開放 */
    free(target);

    /* ノードが1つ減ったのでサイズを減らす*/
    listp->num_of_node--;

    return TRUE;
}

void list_show(list *listp)
{
    node *current;

    printf("<<<show all elements>>>\n");
    for (current = listp->head; current != NULL; current = current->next)
    {
        printf("element: %s\n", current->value);
    }
    printf("\n");
}

void list_free(list *listp)
{
    int max_offset;

    for (max_offset = listp->num_of_node - 1; max_offset >= 0; max_offset--)
    {
        /* 末尾から順に開放 */
        list_remove(listp, max_offset);
    }
}

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


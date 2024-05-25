/* 問1.6 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sset.h"

#define TRUE 1
#define FALSE 0

/*
ssetの初期化。
*/
void sset_init(sset *ssetp)
{
    ssetp->head = NULL;
    ssetp->num_of_node = 0;
}

/*
ssetを全て解放。
*/
void sset_free(sset *ssetp)
{
    node *current, *prev;

    prev = NULL;
    current = ssetp->head;
    while (current != NULL)
    {
        prev = current;
        current = current->next;
        free(prev);
    }
}

/*
ssetのサイズ（要素数）を返す。
*/
int sset_size(sset *ssetp)
{
    return ssetp->num_of_node;
}

/*
要素を追加する。
追加成功でTRUEを、失敗でFALSEを返す。
*/
int sset_add(sset *ssetp, char *value)
{
    node *current, *prev, *new;

    prev = NULL;
    for (current = ssetp->head; current != NULL; current = current->next)
    {
        if (strcmp(value, current->value) <= 0)
        {
            break;
        }

        prev = current;
    }

    new = (node *)xmalloc(NULL, sizeof(node));
    if (new == NULL)
    {
        /* メモリ確保失敗で追加できないのでFALSE */
        return FALSE;
    }

    new->value = value;
    new->next = current;
    if (prev == NULL)
    {
        /* 先頭への追加 */
        ssetp->head = new;
    }
    else
    {
        /* 先頭以外への追加 */
        prev->next = new;
    }

    /* 要素が1つ増えたのでサイズを増やす*/
    ssetp->num_of_node++;

    return TRUE;
}

/*
要素を削除する。
削除成功で削除した要素を、失敗でNULLを返す。
*/
char *sset_remove(sset *ssetp, char *value)
{
    node *target, *prev;
    char *retval;

    prev = NULL;
    for (target = ssetp->head; target != NULL; target = target->next)
    {
        if (strcmp(value, target->value) < 0)
        {
            /* これ以上は調べる必要がないのでbreak */
            break;
        }

        if (strcmp(value, target->value) == 0)
        {
            /* 一致するものが存在 */
            retval = target->value;
            if (prev == NULL)
            {
                /* 先頭にあった場合 */
                ssetp->head = target->next;
            }
            else
            {
                /* 先頭以外にあった場合 */
                prev->next = target->next;
            }

            /* メモリ解放 */
            free(target);

            /* 要素が1つ減ったのでサイズを減らす */
            ssetp->num_of_node--;

            return retval;
        }

        prev = target;
    }

    /* 一致するものがなかったのでFALSE */
    return FALSE;
}

/*
文字列の辞書順において、valueの1つ後にある要素を返す。
見つかればその要素を、見つかれなければNULLを返す。
*/
char *sset_find(sset *ssetp, char *value)
{
    node *current;

    for (current = ssetp->head; current != NULL; current = current->next)
    {
        if (strcmp(value, current->value) <= 0)
        {
            return current->value;
        }
    }

    return NULL;
}

/*
ssetの内容を表示。
*/
void sset_show(sset *ssetp)
{
    node *current;

    printf("<<<show sset elements>>>\n");
    for (current = ssetp->head; current != NULL; current = current->next)
    {
        printf("element: %s\n", current->value);
    }
    printf("\n");
}

/*
メモリの動的確保を行う。
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


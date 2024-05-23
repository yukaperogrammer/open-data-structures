#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "uset_err.h"

#define TRUE 1
#define FALSE 0

static uset *head;
static int uset_size;

void init_uset(void)
{
    head = NULL;
    uset_size = 0;
}

int size(void)
{
    return uset_size;
}

int add(char *element)
{
    uset *current, *prev;

    /* 要素が0個のとき */
    if (head == NULL)
    {
        head = (uset *)xmalloc(NULL, sizeof(uset));
        if (head == NULL)
        {
            fprintf(stderr, "Error: memory allocation\n");
            all_free();
            exit(1);
        }

        /* 文字列コピー */
        strncpy(head->element, element, sizeof(head->element));
        head->next = NULL;
        uset_size++;

        return TRUE;
    }

    /* 要素が0個ではないとき、重複を調べる*/
    for (current = head; current != NULL; current = current->next)
    {
        /* 重複があればFALSEを返す */
        if (strncmp(current->element, element, sizeof(current->element)) == 0)
        {
            return FALSE;
        }

        /* 重複がなかったとき、currentは必ずNULLになるので、1つ前の要素を保存しておく */
        prev = current;
    }

    /* 重複がないとき、末尾に要素を追加する */
    /* ノード1つ分の領域の確保 */
    prev->next = (uset *)xmalloc(NULL, sizeof(uset));
    if (prev->next == NULL)
    {
        fprintf(stderr, "Error: memory allocation\n");
        all_free();
        exit(1);
    }

    /* 文字列コピー */
    strncpy(prev->next->element, element, sizeof(prev->next->element));
    prev->next->next = NULL;
    uset_size++;

    return TRUE;
}

char *remv(char *element)
{
    uset *current, *prev = NULL;

    for (current = head; current != NULL; current = current->next)
    {
        if (strncmp(current->element, element, sizeof(current->element)) == 0)
        {
            if (current == head)
            {
                /* 先頭の次の要素 */
                head = head->next;
            }
            else
            {
                /* 1つ前と1つ後の要素を繋げる */
                prev->next = current->next;
            }
            uset_size--;

            return current->element;
        }

        prev = current;
    }

    return NULL;
}

char *find(char *element)
{
    uset *current;

    for (current = head; current != NULL; current = current->next)
    {
        if (strncmp(current->element, element, sizeof(current->element)) == 0)
        {
            return current->element;
        }
    }

    return NULL;
}

void show_uset(void)
{
    uset *current;
    int i = 0;

    printf("USet elements\n");
    for (current = head, i = 0; current != NULL; current = current->next, i++)
    {
        printf("%d: %s\n", (i + 1), current->element);
    }
    printf("\n");

    return;
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

void all_free(void)
{
    uset *p, *q;

    p = head;
    while (p != NULL)
    {
        q = p;
        p = p->next;
        free(q);
    }

    return;
}


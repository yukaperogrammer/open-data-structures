/* 問1.1-6 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#define LINESIZE 512

void out_sort_asc(FILE *);
int is_duplicate(char **, char *, int);
void sort(char **, int);
void swap(char *, char *);
void output(char **, int);
void all_free(char **, int);
void error_process(char **, FILE *, int);

int main(int argc, char *argv[])
{
    FILE *fp;

    if (argc != 2)
    {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        exit(1);
    }

    fp = fopen(argv[1], "r");
    if (fp == NULL)
    {
        perror(argv[1]);
        exit(1);
    }

    out_sort_asc(fp);

    if (fclose(fp) == EOF)
    {
        perror(argv[1]);
        exit(1);
    }

    return 0;
}

void out_sort_asc(FILE *fp)
{
    char **p;
    char **tmp;
    int i = 0; /* インデックス */
    int n = 1; /* 行数 */

    p = (char **)malloc(sizeof(char *) * n);
    if (p == NULL)
    {
        /* 全て開放して終了 */
        error_process(NULL, fp, 0);
    }
    n++;

    p[i] = (char *)malloc(sizeof(char) * LINESIZE);
    if (p[i] == NULL)
    {
        /* 全て開放して終了 */
        error_process(p, fp, 0);
    }

    while (fgets(p[i], LINESIZE, fp) != NULL)
    {
        if (is_duplicate(p, p[i], i))
        {
            /* 重複しているなら何もしない */
            continue;
        }

        /* 重複していないなら次の領域を確保する */
        tmp = (char **)realloc(p, sizeof(char *) * n);
        if (tmp == NULL)
        {
            /* 全て開放して終了 */
            error_process(p, fp, i + 1);
        }
        p = tmp;
        i++;
        n++;

        p[i] = (char *)malloc(sizeof(char) * LINESIZE);
        if (p[i] == NULL)
        {
            /* 全て開放して終了 */
            error_process(p, fp, i);
        }

        /* ソート（長さ順、辞書順） */
        sort(p, i - 1);
    }

    /* ソート済み表示 */
    output(p, i);

    /* 全て開放して終了 */
    all_free(p, i);

    return;
}

int is_duplicate(char **p, char *s, int end)
{
    int i;

    for (i = 0; i < end; i++)
    {
        if (strcmp(p[i], s) == 0)
        {
            /* true */
            return 1;
        }
    }

    /* false */
    return 0;
}

void sort(char **p, int maxind)
{
    int i;

    /* 短い順にソート */
    for (i = maxind; i > 0; i--)
    {
        if (strlen(p[i]) > strlen(p[i - 1]))
        {
            /* p[i]が一番大きいので、ソートする必要なし */
            break;
        }

        if (strlen(p[i]) == strlen(p[i - 1]))
        {
            /* 長さが同じなら以降辞書順ソート */
            if (strcmp(p[i], p[i - 1]) < 0)
            {
                swap(p[i], p[i - 1]);
                continue;
            }

            break;
        }

        swap(p[i], p[i - 1]);
    }

    return;
}

void swap(char *s1, char *s2)
{
    char tmp[LINESIZE];

    strncpy(tmp, s1, LINESIZE);
    strncpy(s1, s2, LINESIZE);
    strncpy(s2, tmp, LINESIZE);

    return;
}

void output(char **p, int end)
{
    int i;

    for (i = 0; i < end; i++)
    {
        printf("%s", p[i]);
    }

    return;
}

void all_free(char **p, int end)
{
    int i;

    for (i = 0; i < end; i++)
    {
        free(p[i]);
    }
    free(p);

    return;
}

void error_process(char **p, FILE *fp, int end)
{
    if (p != NULL)
    {
        all_free(p, end);
    }
    fprintf(stderr, "%s", strerror(errno));
    fclose(fp);
    exit(1);
}


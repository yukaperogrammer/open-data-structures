/* 問1.1-7 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#define DEFAULTLINES 128 /* デフォルトの行数 */
#define LINESIZE 512     /* 1行の文字数は十分な大きさにしておく */

void out_sort_asc(FILE *);
void sort(char **, int);
void swap(char *, char *);
void output(char **, int);
void *xmalloc(void *, int);
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
    char **p = NULL;
    char **tmp = NULL;
    int i; /* インデックス */
    int n; /* 行数 */

    for (i = 0, n = 0;;)
    {
        /* 行が足りなければ領域を拡張 */
        if (i == DEFAULTLINES * n)
        {
            n++;
            tmp = (char **)xmalloc(p, sizeof(char *) * DEFAULTLINES * n);
            if (tmp == NULL)
            {
                error_process(p, fp, DEFAULTLINES * n);
            }
            p = tmp;
        }

        /* 1行の文字数の領域を確保 */
        p[i] = (char *)xmalloc(NULL, sizeof(char) * LINESIZE);
        if (p[i] == NULL)
        {
            error_process(p, fp, DEFAULTLINES * n);
        }

        /* ファイルを最後まで読み込んだらループを抜ける */
        if (fgets(p[i], LINESIZE, fp) == NULL)
        {
            break;
        }

        sort(p, i);

        i++;
    }

    output(p, i);

    /* 全て開放して終了 */
    all_free(p, i);

    return;
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

void *xmalloc(void *ptr, int size)
{
    void *p;

    if (ptr ==  NULL)
    {
        p = malloc(size);
    }
    else
    {
        p = realloc(ptr, size);
    }

    return p;
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


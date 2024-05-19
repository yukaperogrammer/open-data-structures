/* 問1.1-8 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#define DEFAULTLINES 128 /* デフォルトの保持行数 */
#define LINESIZE 512     /* 1行の文字数 */

void out_evenodd(FILE *);
void *xmalloc(void *, int);
void output(char **, int);
void all_free(char **, int);
void error_process(char **p, FILE *, int);

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

    out_evenodd(fp);

    if (fclose(fp) == EOF)
    {
        perror(argv[1]);
        exit(1);
    }

    return 0;
}

void out_evenodd(FILE *fp)
{
    char **p = NULL;
    char **tmp = NULL;
    int i; /* インデックス */
    int n; /* 行の拡張回数 */

    for (i = 0, n = 0;;)
    {
        /* 行数が足りなくなったら拡張 */
        if (i == DEFAULTLINES * n)
        {
            n++;
            tmp = (char **)xmalloc(p, sizeof(char *) * DEFAULTLINES * n);
            if (tmp == NULL)
            {
                /* メモリの確保に失敗したら全開放して終了 */
                error_process(p, fp, DEFAULTLINES * (n - 1));
            }
            p = tmp;
        }

        /* 1行分のメモリを確保 */
        p[i] = (char *)xmalloc(NULL, sizeof(char) * LINESIZE);
        if (p[i] == NULL)
        {
            /* メモリの確保に失敗したら全開放して終了 */
            error_process(p, fp, DEFAULTLINES * n);
        }

        /* 最後まで読み込んだら終了 */
        if (fgets(p[i], LINESIZE, fp) == NULL)
        {
            break;
        }

        i++;
    }

    /* 表示 */
    output(p, i);

    /* メモリ全開放 */
    all_free(p, DEFAULTLINES * n);

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

void output(char **p, int end)
{
    int i;

    /* 偶数行表示 */
    printf("<<<偶数行表示>>>\n");
    for (i = 0; i < end; i += 2)
    {
        printf("%s", p[i]);
    }
    printf("\n\n");

    /* 奇数行表示 */
    printf("<<<奇数行表示>>>\n");
    for (i = 1; i < end; i += 2)
    {
        printf("%s", p[i]);
    }

    printf("\n");

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
    fclose(fp);
    fprintf(stderr, "%s\n", strerror(errno));
    exit(1);
}


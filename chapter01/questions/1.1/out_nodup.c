/* 問1.1-4 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#define LINESIZE 512 /* 1行のサイズは十分なサイズにしておく */

void out_nodup(FILE *);
int is_duplicate(char **, char *, int);
void *xmalloc(void *, int);
void all_free(char **, int);
void error_process(char **, FILE *, int);
void output(char **, int);

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

    out_nodup(fp);

    if (fclose(fp) == EOF)
    {
        perror(argv[1]);
        exit(1);
    }

    return 0;
}

void out_nodup(FILE *fp)
{
    char **p = NULL;
    char **tmp = NULL;
    int i; /* インデックス */
    int n; /* 行数 */

    for (i = 0, n = 0;;)
    {
        if (i == n)
        {
            /* 行の領域を確保 */
            n++;
            tmp = (char **)xmalloc(p, sizeof(char *) * n);
            if (tmp == NULL)
            {
                /* 全開放して終了 */
                error_process(p, fp, n);
            }
            p = tmp;
        }

        /* 1行の文字数の領域を確保 */
        p[i] = (char *)xmalloc(NULL, sizeof(char) * LINESIZE);
        if (p[i] == NULL)
        {
            /* 全開放して終了 */
            error_process(p, fp, n);
        }

        /* ファイルを最後まで読み込んだらループを抜ける */
        if (fgets(p[i], LINESIZE, fp) == NULL)
        {
            break;
        }

        /* 読み込んだ行が重複しているなら確保済みの領域に次の行を読み込む */
        if (is_duplicate(p, p[i], i))
        {
            continue;
        }

        i++;
    }

    /* 重複していない行を表示 */
    output(p, i);

    /* 全開放 */
    all_free(p, n);

    return;
}

int is_duplicate(char **p, char *s, int end)
{
    int i;

    for (i = 0; i < end; i++)
    {
        if (strncmp(p[i], s, LINESIZE) == 0)
        {
            /* true */
            return 1;
        }
    }

    /* false */
    return 0;
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
    fprintf(stderr, "%s\n", strerror(errno));
    fclose(fp);
    exit(1);
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


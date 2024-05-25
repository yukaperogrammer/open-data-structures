/* 問1.1-5 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#define LINESIZE 512 /* 1行のサイズは十分な大きさにしておく */

void out_dup(FILE *);
void *xmalloc(void *, int);
void all_free(char **, int);
void error_process(char **, FILE *, int);
int is_duplicate(char **, char *, int);

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

    out_dup(fp);

    if (fclose(fp) == EOF)
    {
        perror(argv[1]);
        exit(1);
    }

    return 0;
}

void out_dup(FILE *fp)
{
    char **p = NULL;
    char **tmp = NULL;
    int i; /* インデックス */
    int n; /* 行数 */

    for (i = 0, n = 0;;)
    {
        if (i == n)
        {
            /* 行の領域の確保 */
            n++;
            tmp = (char **)xmalloc(p, sizeof(char *) * n);
            if (tmp == NULL)
            {
                error_process(tmp, fp, n);
            }
            p = tmp;
        }

        /* 1行の文字数の領域の確保 */
        p[i] = (char *)xmalloc(NULL, sizeof(char) * LINESIZE);
        if (p[i] == NULL)
        {
            error_process(p, fp, n);
        }

        /* ファイルを最後まで読み込んだらループを抜ける */
        if (fgets(p[i], LINESIZE, fp) == NULL)
        {
            break;
        }

        if (is_duplicate(p, p[i], i))
        {
            /* 行が重複していたら表示して次の行は確保済みの領域に読み込む */
            printf("%s", p[i]);
            continue;
        }

        i++;
    }

    /* 全開放 */
    all_free(p, n);

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


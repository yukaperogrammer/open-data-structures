/* 問1.1-5 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#define LINESIZE 512 /* 1行のサイズは十分な大きさにしておく */

void read_file(FILE *);
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

    /* 重複している行を出力 */
    read_file(fp);

    if (fclose(fp) == EOF)
    {
        perror(argv[1]);
        exit(1);
    }

    return 0;
}

void read_file(FILE *fp)
{
    char **p;
    char **tmp;
    int i = 0; /* インデックス */
    int n = 1; /* 行数 */

    /* 最初の1行分を確保 */
    p = (char **)malloc(sizeof(char *) * n);
    if (p == NULL)
    {
        /* 失敗したら全開放して終了 */
        error_process(NULL, fp, 0);
    }
    n++;

    p[i] = (char *)malloc(sizeof(char) * LINESIZE);
    if (p[i] == NULL)
    {
        /* 失敗したら全開放して終了 */
        error_process(p, fp, 0);
    }

    while (fgets(p[i], LINESIZE, fp) != NULL)
    {
        /* 重複しているなら表示するだけ */
        if (is_duplicate(p, p[i], i))
        {
            printf("%s", p[i]);
            continue;
        }

        tmp = (char **)realloc(p, sizeof(char *) * n);
        if (tmp == NULL)
        {
            /* 失敗したら全開放して終了 */
            error_process(p, fp, i + 1);
        }
        p = tmp;
        i++;
        n++;

        p[i] = (char *)malloc(sizeof(char) * LINESIZE);
        if (p[i] == NULL)
        {
            /* 失敗したら全開放して終了 */
            error_process(p, fp, i);
        }
    }

    /* 全開放して終了 */
    all_free(p, i + 1);

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


/* 問1.1-9 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <errno.h>

#define DEFAULTLINES 128         /* デフォルトの行数 */
#define LINESIZE 512             /* 1行のサイズは十分な大きさにしておく */
#define SHUFFLE_MAGNIFICATION 10 /* この値をかけてシャッフル回数を増やす */

void out_random(FILE *);
void output_random(char **, int, int);
void swap(char *, char *);
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

    out_random(fp);

    if (fclose(fp) == EOF)
    {
        perror(argv[1]);
        exit(1);
    }

    return 0;
}

void out_random(FILE *fp)
{
    char **p = NULL;
    char **tmp = NULL;
    int i; /* インデックス */
    int n; /* 行の拡張回数 */

    for (i = 0, n = 0;;)
    {
        /* 行が足りないなら領域を拡張 */
        if (i == DEFAULTLINES * n)
        {
            n++;
            tmp = (char **)xmalloc(p, sizeof(char *) * DEFAULTLINES * n);
            if (tmp == NULL)
            {
                /* 全開放して終了 */
                error_process(p, fp, DEFAULTLINES * n);
            }
            p = tmp;
        }

        /* 1行の文字数の領域を確保 */
        p[i] = (char *)xmalloc(NULL, sizeof(char) * LINESIZE);
        if (p[i] == NULL)
        {
            /* 全開放して終了 */
            error_process(p, fp, DEFAULTLINES * n);
        }

        /* ファイルを全て読み込んだらループを抜ける */
        if (fgets(p[i], LINESIZE, fp) == NULL)
        {
            break;
        }

        i++;
    }

    output_random(p, n, i);

    all_free(p, i);

    return;
}

void output_random(char **p, int n, int max)
{
    int i;
    int j, k;

    srand((unsigned int)time(NULL));

    for (i = 0; i < SHUFFLE_MAGNIFICATION * DEFAULTLINES * n; i++)
    {
        /* 乱数をmaxで割った余りの値をインデックスとして交換する*/
        j = rand() % max;
        k = rand() & max;
        if (j == k)
        {
            /* 同じインデックスは交換しない */
            continue;
        }
        swap(p[j], p[k]);
    }

    for (i = 0; i < max; i++)
    {
        printf("%s", p[i]);
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
    fprintf(stderr, "%s", strerror(errno));
    all_free(p, end);
    fclose(fp);
    exit(1);
}


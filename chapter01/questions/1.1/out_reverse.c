/* 問1.1-1 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#define LINESIZE 512    /* 1行のサイズは十分な大きさにしておく */ 
#define DEFAULTLINES 128 /* デフォルトの行数 */

void out_reverse(FILE *);
void *xmalloc(void *, int);
void output_reverse(char **, int);
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
    if (!fp)
    {
        perror(argv[1]);
        exit(1);
    }

    out_reverse(fp);

    if (fclose(fp) == EOF)
    {
        perror(argv[1]);
        exit(1);
    }

    return 0;
}

void out_reverse(FILE *fp)
{
    char **p = NULL;
    char **tmp = NULL;
    int i;
    int n;

    for (i = 0, n = 0;;)
    {
        /* 行が足りなくなったら拡張 */
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

        p[i] = (char *)xmalloc(NULL, sizeof(char) * LINESIZE);
        if (p[i] == NULL)
        {
            /* 全開放して終了 */
            error_process(p, fp, DEFAULTLINES * n);
        }

        if (fgets(p[i], LINESIZE, fp) == NULL)
        {
            break;
        }

        i++;
    }

    /* 逆順に表示 */
    output_reverse(p, i);

    /* 全開放 */
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

void output_reverse(char **p, int end)
{
    int i;

    for (i = end; i >= 0; i--)
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
    fprintf(stderr, "%s\n", strerror(errno));
    fclose(fp);
    exit(1);
}


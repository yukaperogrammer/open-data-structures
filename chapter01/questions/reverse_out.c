/* 問1.1-1 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#define LINESIZE 512    /* 1行のサイズは十分な大きさにしておく */ 
#define DEFAULTLINES 64 /* デフォルトの行数 */

void read_file(FILE *);
void reverse_out(char **, int);
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
    int i;
    int n;

    p = (char **)malloc(sizeof(char *) * DEFAULTLINES);
    if (p == NULL)
    {
        error_process(NULL, fp, 0); 
    }
	
    for (i = 0, n = 1;; i++)
    {
        /* 行数が足りなければ拡張する */
        if (i == DEFAULTLINES * n)
        {
            n++;
            tmp = (char **)realloc(p, sizeof(char *) * DEFAULTLINES * n);
            /* メモリの拡張に失敗したら全開放して終了 */
            if (tmp == NULL)
            {
                error_process(p, fp, i - 1);
            }

            p = tmp;
        }

        p[i] = (char *)malloc(sizeof(char) * LINESIZE);
        /* メモリの確保に失敗したら全開放して終了 */
        if (p[i] == NULL)
        {	
            error_process(p, fp, i);
        }

        if (fgets(p[i], LINESIZE, fp) == NULL)
        {
            /* バッファへの読み込みに失敗したら全開放して終了 */
            if (ferror(fp))
            {
                error_process(p, fp, i + 1);
            }

            /* ファイルを最後まで読み込んだのでループを抜ける */
            break;
        }
    }

    /* 逆順に表示 */
    reverse_out(p, i);

    all_free(p, DEFAULTLINES * n);

    return;
}

void reverse_out(char **p, int end)
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


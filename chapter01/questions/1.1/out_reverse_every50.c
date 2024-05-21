/* 問1.1-2 */
#include <stdio.h>
#include <stdlib.h>

#define LINES 50     /* 実行中に保持できる行数は50まで */
#define LINESIZE 512 /* 1行のサイズは十分な大きさにしておく */

void read_file(FILE *);
void reverse_out(char (*)[], int);

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

    /* ファイルの内容を50行毎に逆順に表示する */
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
    char buf[LINES][LINESIZE];
    int i;

    i = 0;
    while (fgets(buf[i], LINESIZE, fp) != NULL)
    {
        i++;

        /* 50行読み込んだら逆順に表示 */
        if (i == LINES)
        {
            reverse_out(buf, LINES - 1);
            i = 0;
        }
    }

    /* 50行丁度読んで終わったらi = 0となっている
       それ以外の場合に残りを逆順に表示 */
    if (i != 0)
    {
        reverse_out(buf, i - 1);
    }

    return;
}

void reverse_out(char (*buf)[LINESIZE], int end)
{
    int i;

    for (i = end; i >= 0; i--)
    {
        printf("%s", buf[i]);
    }
    printf("\n");
}


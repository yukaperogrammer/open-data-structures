/* 問1.1-3 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LINES 43     /* 保持できる行は43行まで */
#define LINESIZE 512 /* 1行のサイズは十分な大きさにしておく */

void read_file(FILE *);

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
    /* リングバッファで保持する */
    char buf[LINES][LINESIZE];
    int i = 0;
    int read_count = 0;

    while (fgets(buf[i], LINESIZE, fp) != NULL)
    {
        read_count++;

        if ((read_count >= LINES) && (strcmp(buf[i], "\n") == 0))
        {
            printf("%s", buf[(i + 1) % LINES]);
        }

        i = (i + 1) % LINES;
    }

    return;
}


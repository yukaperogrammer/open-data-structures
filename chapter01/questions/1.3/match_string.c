/* 問1.3 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STACK_SIZE 64 
#define TRUE 1
#define FALSE 0

static char stack[MAX_STACK_SIZE];
static int stack_size = 0;

int is_matched(char *);
void init_stack(void);
void push(char);
char pop(void);
int is_empty(void);
int is_full(void);

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        fprintf(stderr, "Usage: %s <string>\n", argv[0]);
        exit(1);
    }

    if (is_matched(argv[1]))
    {
        printf("%s is matched\n", argv[1]);
    }
    else
    {
        printf("%s is not matched\n", argv[1]);
    }

    return 0;
}

int is_matched(char *str)
{
    int i;
    int length = strlen(str);

    /*
    '(', '{', '[' のときはスタックにそれぞれ ')', '}', ']' をpush
    ')', '}', ']' のときはスタックをpopし、それぞれ ')', '}', ']' と等しいかチェック
    「全て等しい」かつ「スタックが空」ならば「マッチした文字列」となる
    */
    init_stack();
    for (i = 0; i < length; i++)
    {
        switch (str[i])
        {
            case '(':
                push(')');
                break;

            case ')':
                if (is_empty())
                {
                    return FALSE;
                }
                else
                {
                    if (pop() != ')')
                        return FALSE;
                }
                break;

            case '{':
                push('}');
                break;

            case '}':
                if (is_empty())
                {
                    return FALSE;
                }
                else
                {
                    if (pop() != '}')
                        return FALSE;
                }
                break;

            case '[':
                push(']');
                break;

            case ']':
                if (is_empty())
                {
                    return FALSE;
                }
                else
                {
                    if (pop() != ']')
                        return FALSE;
                }
                break;

            default:
                /* 括弧以外の文字が含まれていたらエラー */
                fprintf(stderr, "%s is invalid\n", str);
                exit(1);
        }
    }

    if (is_empty())
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

void init_stack(void)
{
    int i;

    for (i = 0; i < MAX_STACK_SIZE; i++)
    {
        stack[i] = '\0';
    }

    return;
}

void push(char x)
{
    if (is_full())
    {
        fprintf(stderr, "stack is full\n");
        exit(1);
    }

    stack[stack_size++] = x;

    return;
}

char pop(void)
{
    char c;

    if (is_empty())
    {
        fprintf(stderr, "stack is empty\n");
        exit(1);
    }

    c = stack[--stack_size];
    stack[stack_size] = '\0';

    return c;
}

int is_empty(void)
{
    if (stack_size == 0)
    {
        return TRUE;
    }

    return FALSE;
}

int is_full(void)
{
    if (stack_size == MAX_STACK_SIZE)
    {
        return TRUE;
    }

    return FALSE;
}


/* 問1.4 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STACK_SIZE 64
#define MAX_QUEUE_SIZE 64
#define TRUE 1
#define FALSE 0

/* スタック */
static char stack[MAX_STACK_SIZE];
static int stack_size;

/* キュー */
static char queue[MAX_QUEUE_SIZE]; /* リングバッファ */
static int queue_size;
static int head;
static int tail;

void init_stack(void);
void push(char);
char pop(void);
int is_stack_empty(void);
int is_stack_full(void);
void show_stack(void);
void init_queue(void);
void enqueue(char);
char dequeue(void);
int is_queue_empty(void);
int is_queue_full(void);

int main(int argc, char *argv[])
{
    int length;
    int i;

    if (argc != 2)
    {
        fprintf(stderr, "Usage: %s <string>\n", argv[0]);
        exit(1);
    }

    length = strlen(argv[1]);

    if (length > MAX_STACK_SIZE)
    {
        fprintf(stderr, "%s: too chars\n", argv[1]);
        exit(1);
    }

    init_stack();
    init_queue();

    /* スタックに文字を全てpush */
    for (i = 0; i < length; i++)
    {
        if (is_stack_full() == FALSE)
        {
            push(argv[1][i]);
        }
        else
        {
            fprintf(stderr, "stack is full\n");
            exit(1);
        }
    }

    printf("スタック逆順前\n");
    show_stack();

    /* スタックの要素を全てキューに移す */
    for (i = 0; i < length; i++)
    {
        if (is_stack_empty() == FALSE && is_queue_full() == FALSE)
        {
            enqueue(pop());
        }
        else
        {
            fprintf(stderr, "Error: to queue from stack\n");
            exit(1);
        }
    }

    /* キューの要素を全てスタックに移す */
    for (i = 0; i < length; i++)
    {
        if (is_queue_empty() == FALSE && is_stack_full() == FALSE)
        {
            push(dequeue());
        }
        else
        {
            fprintf(stderr, "Error: to stack from queue\n");
            exit(1);
        }
    }

    printf("スタック逆順後\n");
    show_stack();

    return 0;
}

void init_stack(void)
{
    int i;

    stack_size = 0;

    for (i = 0; i < MAX_STACK_SIZE; i++)
    {
        stack[i] = '\0';
    }

    return;
}

void push(char x)
{
    if (is_stack_full() == TRUE)
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

    if (is_stack_empty() == TRUE)
    {
        fprintf(stderr, "stack is empty\n");
        exit(1);
    }

    c = stack[--stack_size];
    stack[stack_size] = '\0';

    return c;
}

int is_stack_empty(void)
{
    if (stack_size == 0)
    {
        return TRUE;
    }

    return FALSE;
}

int is_stack_full(void)
{
    if  (stack_size == MAX_STACK_SIZE)
    {
        return TRUE;
    }

    return FALSE;
}

void show_stack(void)
{
    int i;

    for (i = 0; i < stack_size; i++)
    {
        printf("%c", stack[i]);
    }
    printf("\n");

    return;
}

void init_queue(void)
{
    int i;

    head = 0;
    tail = 0;
    queue_size = 0;

    for (i = 0; i < MAX_QUEUE_SIZE; i++)
    {
        queue[i] = '\0';
    }

    return;
}

void enqueue(char x)
{
    if (is_queue_full() == TRUE)
    {
        fprintf(stderr, "queue is full\n");
        exit(1);
    }

    queue[tail] = x;
    tail = (tail + 1) % MAX_QUEUE_SIZE;
    queue_size++;
    
    return;
}

char dequeue(void)
{
    char c;

    if (is_queue_empty() == TRUE)
    {
        fprintf(stderr, "queue is empty\n");
        exit(1);
    }

    c = queue[head]; 
    queue[head] = '\0';
    head = (head + 1) % MAX_QUEUE_SIZE;
    queue_size--;

    return c;
}

int is_queue_empty(void)
{
    if (queue_size == 0)
    {
        return TRUE;
    }

    return FALSE;
}

int is_queue_full(void)
{
    if (queue_size == MAX_QUEUE_SIZE)
    {
        return TRUE;
    }

    return FALSE;
}


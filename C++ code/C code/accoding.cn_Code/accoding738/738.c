#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define MAXSIZE 22
struct curQueue
{
    int queue[MAXSIZE];
    int rear, front;
};
void enqueue(struct curQueue *q, int item)
{
    q->rear = (q->rear + 1) % MAXSIZE;
    q->queue[q->rear] = item;
}
int dequeue(struct curQueue *q)
{
    int tmp = q->queue[q->front];
    q->front = (q->front + 1) % MAXSIZE;
    return tmp;
}
int topqueue(struct curQueue *q)
{
    return q->queue[q->front];
}
int main()
{
    int n, tmp;
    while (scanf("%d", &n) != EOF)
    {
        struct curQueue *q = (struct curQueue *)malloc(sizeof(struct curQueue));
        q->front = 0, q->rear = MAXSIZE - 1;
        enqueue(q, 1);
        for (int i = 2; i <= n + 1; i++)
        {
            enqueue(q, 1);
            for (int j = 1; j <= i - 2; j++)
            {
                tmp = dequeue(q);
                printf("%d ", tmp);
                tmp += topqueue(q);
                enqueue(q, tmp);
            }
            enqueue(q, 1);
            printf("%d ", dequeue(q));
            putchar('\n');
        }
        free(q);
    }
    return 0;
}
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#define maxm 100
#define qsize 100
struct queue
{
    int size;
    int queue[qsize];
    int head, tail;
} que;
void init()
{
    memset(que.queue, 0, sizeof(int) * qsize);
    que.head = -1;
    que.tail = -1;
    que.size = 0;
}
int top()
{
    if (que.size == 0)
        return -1;
    return que.queue[que.head];
}
void push(int x)
{
    if (que.size > qsize)
        return;
    que.tail = (que.tail + 1) % qsize;
    que.queue[que.tail] = x;
    que.size++;
}
void pop()
{
    if (que.size <= 0)
        return;
    que.head = (que.head + 1) % qsize;
    que.size--;
}
int isempty()
{
    return !que.size;
}
int ver[maxm], color[maxm], dis[maxm], pre[maxm];
int a[maxm][maxm];
void bfs(int start, int ver_num)
{
    init();
    for (int i = 1; i <= ver_num; i++)
    {
        color[i] = 0;
        dis[i] = 0x3fffffff;
        pre[i] = -1;
    }
    color[start] = 1;
    dis[start] = 0;
    pre[start] = -1;
    push(start);
    int u;
    while (!isempty())
    {
        u = top(), pop();
        for (int i = 1; i <= ver_num; i++)
        {
            if (i != u && a[u][i] == 1)
            {
                if (color[i] == 0)
                {
                    color[i] = 1;
                    dis[i] = dis[u] + 1;
                    pre[i] = u;
                    push(i);
                }
            }
        }
        color[u] = 2;
    }
}
int main()
{
    int n, m; //n个节点，m条边
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
            scanf("%d", &a[i][j]);
    }
    bfs(1, n);
    for (int i = 1; i <= n; i++)
        printf("%d ", dis[i]);
    return 0;
}

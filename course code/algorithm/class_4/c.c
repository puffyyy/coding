#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <limits.h>
#define maxm 205
#define qsize maxm
#define LMAX 0X3ffffffffffffff
long long gr[maxm][maxm], gf[maxm][maxm], g[maxm][maxm];
int path[maxm], pre[maxm];
int visit[maxm];
struct queue
{
    int size;
    int queue[qsize];
    int head, tail;
} que;
void init()
{
    memset(que.queue, 0, sizeof(int) * qsize);
    que.head = 0;
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
void creatGraph(int n, int m)
{
    int s, e;
    long long w;
    // for (int i = 1; i <= n; i++)
    //     for (int j = 1; j <= n; j++)
    //         g[i][j] = LMAX;
    for (int i = 0; i < m; i++)
    {
        scanf("%d%d%lld", &s, &e, &w);
        g[s][e] += w;
        // if (g[s][w] == LMAX)
        //     g[s][e] = w;
        // else
        //     g[s][w] += w;
    }
}
int bfs(int ver_num, int source, int terminal)
{
    if (source == terminal)
        return 0;
    init();
    memset(visit, 0, sizeof(visit));
    memset(pre, 0, sizeof(pre));
    visit[source] = 1;
    pre[source] = -1;
    push(source);
    int u;
    while (!isempty())
    {
        u = top(), pop();
        if (u == terminal)
            return 1;
        for (int i = 1; i <= ver_num; i++)
        {
            if (visit[i] == 0 && gr[u][i] != LMAX && gr[u][i] != 0)
            {
                pre[i] = u;
                visit[i] = 1;
                push(i);
            }
        }
    }
    return 0;
}
void maximum_flow(int n, int s, int t)
{
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
            // if (g[i][j] != LMAX)
            gr[i][j] = g[i][j];
        // else
        // gr[i][j] = 0;
    }
    while (bfs(n, s, t))
    {
        long long minadd = LMAX;
        int next = t;
        while (next != s)
        {
            if (minadd > gr[pre[next]][next])
                minadd = gr[pre[next]][next];
            next = pre[next];
        }
        next = t;
        while (next != s)
        {
            gf[pre[next]][next] += minadd;
            gr[pre[next]][next] -= minadd;
            gr[next][pre[next]] += minadd;
            next = pre[next];
        }
    }
}
int main()
{
    long long ans = 0;
    int n, m, s, t;
    scanf("%d%d%d%d", &n, &m, &s, &t);
    creatGraph(n, m);
    maximum_flow(n, s, t);
    for (int i = 1; i <= n; i++)
    {
        if (gf[s][i] != LMAX && i != s)
            ans += gf[s][i];
    }
    printf("%lld\n", ans);
    return 0;
}
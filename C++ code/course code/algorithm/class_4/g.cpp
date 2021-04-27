#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include <stack>
#include <queue>
#include <set>
using namespace std;
typedef long long ll;
#define maxm 205
#define qsize maxm
int gr[maxm][maxm];
int pre[maxm], visit[maxm];
struct edge
{
    int s, e, w;
} edges[maxm];
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
            if (visit[i] == 0 && gr[u][i] != 0)
            {
                pre[i] = u;
                visit[i] = 1;
                push(i);
            }
        }
    }
    return 0;
}
int maxflow(int n, int s, int t)
{
    int sum = 0;
    int next;
    int minadd;
    while (bfs(n, s, t))
    {
        minadd = 1 << 9;
        next = t;
        while (next != s)
        {
            if (minadd > gr[pre[next]][next])
                minadd = gr[pre[next]][next];
            next = pre[next];
        }
        next = t;
        while (next != s)
        {
            gr[pre[next]][next] -= minadd;
            gr[next][pre[next]] += minadd;
            next = pre[next];
        }
        sum += minadd;
    }
    return sum;
}
int main()
{
    int n, m;
    int w;
    scanf("%d%d", &n, &m);
    for (int i = 0; i < m; i++)
        scanf("%d%d%d", &edges[i].s, &edges[i].e, &edges[i].w);
    for (int i = 0; i < m; i++)
    {
        memset(gr, 0, sizeof(gr));
        w = edges[i].w;
        for (int j = 0; j < m; j++)
        {
            if (i != j && edges[j].w < w)
            {
                gr[edges[j].s][edges[j].e] = 1;
                gr[edges[j].e][edges[j].s] = 1;
            }
        }
        printf("%d ", maxflow(n, edges[i].s, edges[i].e));
    }
    return 0;
}
//0 0 2 0 0 0 0 0 2 1 0 2 1

/*
7 13 
1 7 1
1 2 5
1 3 6
1 4 5
2 3 2
2 5 3
3 4 3
3 5 3
3 6 7
4 6 5
5 6 1
5 7 8
6 7 7
*/
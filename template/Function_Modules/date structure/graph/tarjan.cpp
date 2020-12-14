#include <iostream> //输出所有强连通分量
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
int n, m, x, y, top = 0, cnt = 0, t, col;
int d[200020], a[200020], c[200020], f[200020];
int dfn[200020];
int low[200020];
int stack[200020];
bool v[200020];
struct edge
{
    int u, v, w;
    int next;
} e[1000020];
void Add(int u, int v, int w)
{
    ++top;
    e[top].u = u;
    e[top].v = v;
    e[top].w = w;
    e[top].next = f[u];
    f[u] = top;
}
int read()
{
    int x = 0;
    int k = 1;
    char c = getchar();
    while (c > '9' || c < '0')
    {
        if (c == '-')
            k = -1;
        c = getchar();
    }
    while (c >= '0' && c <= '9')
        x = x * 10 + c - '0',
        c = getchar();
    return x * k;
}
void tarjan(int now)
{
    dfn[now] = low[now] = ++cnt;
    stack[++t] = now;
    v[now] = 1;
    for (int i = f[now]; i != -1; i = e[i].next)
        if (!dfn[e[i].v])
        {
            tarjan(e[i].v);
            low[now] = min(low[now], low[e[i].v]);
        }
        else if (v[e[i].v])
            low[now] = min(low[now], dfn[e[i].v]);
    int cur;
    if (dfn[now] == low[now])
    {
        do
        {
            cur = stack[t--];
            v[cur] = false;
            printf("%d ", cur);
        } while (now != cur);
        printf("\n");
    }
}
int main()
{
    n = read();
    m = read();
    memset(f, -1, sizeof f);
    for (int i = 1; i <= n; ++i)
        a[i] = read();
    for (int i = 1; i <= m; ++i)
    {
        x = read();
        y = read();
        Add(x, y, 0);
    }
    for (int i = 1; i <= n; ++i)
        if (!dfn[i])
            tarjan(i);
    return 0;
}
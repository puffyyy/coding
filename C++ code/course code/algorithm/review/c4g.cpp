#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include <queue>
using namespace std;
#define inf 0x3fffffff
const int maxn = 50005;
struct Edge
{
    int to, w, next;
} edges[maxn];
int head[maxn];
int deepth[maxn];
int cur[maxn]; //当前弧优化
int n, m, cnt;
void init()
{
    memset(head, -1, sizeof(head));
    cnt = 0;
}
void add_edge(int u, int v, int w)
{
    edges[cnt].to = v, edges[cnt].w = w;
    edges[cnt].next = head[u];
    head[u] = cnt++;
    edges[cnt].to = u, edges[cnt].w = 0; //反向边
    edges[cnt].next = head[v];
    head[v] = cnt++;
}
bool bfs(int s, int t)
{
    memset(deepth, 0, sizeof(deepth));
    queue<int> que;
    que.push(s);
    deepth[s] = 1;
    int u;
    while (que.size())
    {
        u = que.front(), que.pop();
        for (int i = head[u]; ~i; i = edges[i].next)
        {
            if (edges[i].w > 0 && deepth[edges[i].to] == 0)
            {
                deepth[edges[i].to] = deepth[u] + 1;
                if (edges[i].to == t)
                    return true;
                que.push(edges[i].to);
            }
        }
    }
    return false; //没有一条路径可以到达t
}
int dfs(int s, int t, int dist) //dist 当前流量
{
    if (s == t || dist == 0)
        return dist;
    int flow = 0, temp_f;
    for (int &i = cur[s]; ~i; i = edges[i].next) //i 是 cur[s]的引用
    {
        if (edges[i].w > 0 && deepth[s] + 1 == deepth[edges[i].to])
        {
            temp_f = dfs(edges[i].to, t, min(dist - flow, edges[i].w));
            edges[i].w -= temp_f;
            edges[i ^ 1].w += temp_f;
            flow += temp_f;
            // if (edges[i].w > 0)
            //     cur[s] = i;
            if (flow == dist)
                break;
        }
    }
    return flow;
}
int dinic(int s, int t)
{
    int flow = 0;
    while (bfs(s, t))
    {
        for (int i = 0; i <= n; i++) //此处的n是顶点个数 即head的个数
            cur[i] = head[i];
        flow += dfs(s, t, inf);
    }
    return flow;
}
struct node
{
    int a, b, c;
} e[105];
int main()
{
    int s, t;
    scanf("%d%d", &n, &m);
    int from, to, wei;
    for (int i = 0; i < m; i++)
        scanf("%d%d%d", &e[i].a, &e[i].b, &e[i].c);

    for (int i = 0; i < m; i++)
    {
        int ccc = e[i].c;
        s = e[i].a, t = e[i].b;
        init();
        for (int j = 0; j < m; j++)
        {
            if (e[j].c < ccc && i != j)
            {
                add_edge(e[j].a, e[j].b, 1);
                add_edge(e[j].b, e[j].a, 1);
            }
        }
        printf("%d ", dinic(s, t));
    }

    return 0;
}
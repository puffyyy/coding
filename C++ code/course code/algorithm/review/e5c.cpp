#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include <queue>
using namespace std;
typedef long long ll;
#define inf 0x3fffffffffffffff
const ll maxn = 50005;
struct Edge
{
    ll to, w, next;
} edges[maxn];
ll head[maxn];
ll deepth[maxn];
ll cur[maxn]; //当前弧优化
ll cnt;
void init()
{
    memset(head, -1, sizeof(head));
    cnt = 0;
}
void add_edge(ll u, ll v, ll w)
{
    edges[cnt].to = v, edges[cnt].w = w;
    edges[cnt].next = head[u];
    head[u] = cnt++;
    edges[cnt].to = u, edges[cnt].w = 0; //反向边
    edges[cnt].next = head[v];
    head[v] = cnt++;
}
bool bfs(ll s, ll t)
{
    memset(deepth, 0, sizeof(deepth));
    queue<ll> que;
    que.push(s);
    deepth[s] = 1;
    ll u;
    while (que.size())
    {
        u = que.front(), que.pop();
        for (ll i = head[u]; ~i; i = edges[i].next)
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
ll dfs(ll s, ll t, ll dist) //dist 当前流量
{
    if (s == t || dist == 0)
        return dist;
    ll flow = 0, temp_f;
    for (ll &i = cur[s]; ~i; i = edges[i].next) //i 是 cur[s]的引用
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
ll dinic(ll n, ll s, ll t)
{
    ll flow = 0;
    while (bfs(s, t))
    {
        for (ll i = 0; i <= n; i++) //此处的n是顶点个数 即head的个数
            cur[i] = head[i];
        flow += dfs(s, t, inf);
    }
    return flow;
}
int a[32][32];
int main()
{
    int n, m;
    scanf("%d%d", &m, &n);
    int s = 0, t = n * m + 1;
    ll sum = 0;
    for (int i = 1; i <= m; i++)
        for (int j = 1; j <= n; j++)
        {
            scanf("%d", &a[i][j]);
            sum += a[i][j];
        }
    init();
    for (int i = 1; i <= m; i++)
        for (int j = 1; j <= n; j++)
        {
            if ((i + j) & 1)
                add_edge(0, n * (i - 1) + j, a[i][j]);
            else
            {
                add_edge(n * (i - 1) + j, n * m + 1, a[i][j]);
                if (i != 1)
                    add_edge(n * (i - 2) + j, n * (i - 1) + j, inf);
                if (i != m)
                    add_edge(n * i + j, n * (i - 1) + j, inf);
                if (j != 1)
                    add_edge(n * (i - 1) + j - 1, n * (i - 1) + j, inf);
                if (j != n)
                    add_edge(n * (i - 1) + j + 1, n * (i - 1) + j, inf);
            }
        }

    printf("%lld", sum - dinic(n * m + 1, s, t));
    return 0;
}
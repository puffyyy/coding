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
#define inf 0x3fffffffffffffff
typedef long long ll;
const ll maxn = 1005;
const ll MS = 1e5 + 5 + maxn;

struct Edge
{
    ll to, w, next;
} edges[MS];
ll head[maxn];
ll deepth[maxn];
ll cur[maxn]; //当前弧优化
ll n, m, cnt;
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
}
void add_edges(ll u, ll v, ll w)
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
            if (flow == dist)
                break;
        }
    }
    return flow;
}
ll dinic(ll s, ll t)
{
    ll flow = 0;
    while (bfs(s, t))
    {
        for (ll i = 0; i <= t; i++) //此处的n是顶点个数 即head的个数
            cur[i] = head[i];
        flow += dfs(s, t, inf);
    }
    return flow;
}
ll minweight[maxn];
ll c[maxn];
struct nodes
{
    ll a, b;
} e[MS];
ll find_edges(ll source, ll n)
{
    ll cnt = 0;
    for (ll s = 1; s < n; s++)
    {
        for (ll i = head[s]; ~i; i = edges[i].next)
        {
            if (edges[i].w + minweight[s] == minweight[edges[i].to])
            {
                e[cnt].a = s, e[cnt].b = edges[i].to;
                cnt++;
            }
        }
    }
    return cnt;
}
bool vfound[maxn];
void dijkstra(ll source, ll n)
{
    for (ll i = 0; i <= n; i++)
    {
        minweight[i] = inf;
        vfound[i] = 0;
    }
    for (ll i = head[1]; ~i; i = edges[i].next)
    {
        minweight[edges[i].to] = edges[i].w;
    }
    minweight[source] = 0;
    vfound[source] = 1;
    for (ll i = 0; i < n - 1; i++)
    {
        ll v, min = inf;
        for (ll j = 0; j < n; j++) //找未访问过的最小路径的边
        {
            if (!vfound[j] && (min > minweight[j]))
            {
                min = minweight[j];
                v = j;
            }
        }
        vfound[v] = 1;
        for (ll i = head[v]; ~i; i = edges[i].next)
        {
            if (!vfound[edges[i].to] && (min + edges[i].w) < minweight[edges[i].to])
                minweight[edges[i].to] = min + edges[i].w;
        }
    }
}
int main()
{
    scanf("%lld%lld", &n, &m);
    init();
    for (ll i = 0; i < m; i++)
    {
        ll s, e, w;
        scanf("%lld%lld%lld", &s, &e, &w);
        add_edge(s, e, w);
        add_edge(e, s, w);
    }
    for (ll i = 1; i <= n; i++)
        scanf("%lld", c + i);

    dijkstra(1, n);
    ll cnt = find_edges(1, n);

    init();
    add_edges(0, 1, inf), add_edges(2 * n, 2 * n + 1, inf);
    add_edges(1, 1 + n, inf);
    for (ll i = 2; i < n; i++)
        add_edges(i, i + n, c[i]);
    add_edges(n, n + n, inf);
    for (ll s = 0; s < cnt; s++)
    {
        add_edges(e[s].a + n, e[s].b, inf);
    }

    printf("%lld", dinic(0, 2 * n + 1));
    return 0;
}
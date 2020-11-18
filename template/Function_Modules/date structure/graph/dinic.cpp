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
ll dinic(ll s, ll t)
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
int main()
{
    ll s, t;
    scanf("%lld%lld%lld%lld", &n, &m, &s, &t);
    ll from, to, wei;
    init();
    for (ll i = 0; i < m; i++)
    {
        scanf("%lld%lld%lld", &from, &to, &wei);
        add_edge(from, to, wei);
    }
    printf("%lld", dinic(s, t));
    return 0;
}
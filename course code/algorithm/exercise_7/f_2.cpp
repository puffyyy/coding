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
struct Edge
{
    ll to, w, next;
} edges[80005];
ll head[20005];
ll deepth[20005];
ll cur[20005]; //当前弧优化
ll n, cnt;
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
    return false;
}
ll dfs(ll s, ll t, ll dist)
{
    if (s == t || dist == 0)
        return dist;
    ll flow = 0, temp_f;
    for (ll &i = cur[s]; ~i; i = edges[i].next)
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
        for (ll i = 0; i <= 2 * n + 1; i++) //此处的n是顶点个数 即head的个数
            cur[i] = head[i];
        flow += dfs(s, t, inf);
    }
    return flow;
}
int main()
{
    while (~scanf("%lld", &n))
    {

        ll to;
        init();
        for (int i = 1; i <= n; i++)
            add_edge(0, i, 1);
        for (int i = 1; i <= n; i++)
            add_edge(i + n, 2 * n + 1, 1);
        for (ll i = 1; i <= n; i++)
        {
            scanf("%lld", &to);
            if (to > 0)
            {
                add_edge(i, n + to, 1);
                add_edge(n + to, i, 1);
            }
        }
        for (ll i = 1; i <= n; i++)
        {
            scanf("%lld", &to);
            if (to > 0)
            {
                add_edge(i + n, to, 1);
                add_edge(to, i + n, 1);
            }
        }
        printf("%lld\n", n - dinic(0, 2 * n + 1));
    }
    return 0;
}
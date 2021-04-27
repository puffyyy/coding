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
#define inf 0x3f3f3f3f3f3f3f3f
const int VER = 550;
vector<int> to[VER];
vector<int> val[VER]; // ll
ll dis[VER];

const int maxe = 1e5 + (VER << 2);
const int maxn = VER << 2;
struct Edge
{
    ll to, w, next;
} edges[maxe];
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
ll dinic(int n, ll s, ll t)
{
    ll flow = 0;
    while (bfs(s, t))
    {
        for (ll i = 0; i <= 2 * n + 1; i++)
            cur[i] = head[i];
        flow += dfs(s, t, inf);
    }
    return flow;
}
void spfa(int n, int s)
{
    int u, v, w;
    int visit[VER];
    queue<int> que;
    memset(visit, 0, sizeof(visit));
    for (int i = 1; i <= n; i++)
        dis[i] = inf;
    dis[s] = 0, visit[s] = 1;
    que.push(s);

    while (que.size())
    {
        u = que.front(), que.pop();
        visit[u] = 0;
        for (int i = 0; i < to[u].size(); i++)
        {
            v = to[u][i];
            w = val[u][i];
            if (dis[v] > dis[u] + w)
            {
                dis[v] = dis[u] + w;
                if (!visit[v])
                    que.push(v), visit[v] = 1;
            }
        }
    }
}
int c[VER];
int main()
{
    int n, m;
    scanf("%d%d", &n, &m);
    int a, b, v;
    for (int i = 0; i < m; i++)
    {
        scanf("%d%d%d", &a, &b, &v);
        to[a].push_back(b);
        val[a].push_back(v);
        to[b].push_back(a);
        val[b].push_back(v);
    }
    spfa(n, 1);
    for (int i = 1; i <= n; i++)
    {
        scanf("%d", &c[i]);
    }
    int s, t;
    s = 0, t = 2 * n + 1;
    init();
    add_edge(s, 1, inf), add_edge(2 * n, t, inf);
    add_edge(1, 1 + n, inf);
    for (int i = 2; i < n; i++)
        add_edge(i, i + n, c[i]);
    add_edge(n, n + n, inf);
    for (int i = 1; i <= n; i++)
    {
        int v, cost;
        for (int j = 0; j < to[i].size(); j++)
        {
            v = to[i][j], cost = val[i][j];
            if (dis[v] == dis[i] + cost)
                add_edge(i + n, v, inf);
        }
    }
    printf("%lld", dinic(n, s, t));
    return 0;
}

/*
3 2 
1 2 5
2 3 6
3 
4
2
*/
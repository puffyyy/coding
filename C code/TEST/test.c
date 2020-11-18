#include <bits/stdc++.h>
#define inf 0x3fffffff
using namespace std;
typedef long long ll;
const ll oo = LLONG_MAX / 4;
inline ll read()
{
    ll x = 0, f = 1;
    char c = getchar();
    while (!isdigit(c))
    {
        if (c == '-')
            f = -1;
        c = getchar();
    }
    while (isdigit(c))
    {
        x = x * 10 + c - '0';
        c = getchar();
    }
    return x * f;
}
const int maxn = 50005;
ll st, ed, tmp[maxn], first[maxn], n, m, cur[maxn], d[maxn], vis[maxn], a, b, c;
int sign;
struct node
{
    ll to, w, next;
} edge[2000010];
void add_edge(int u, int v, ll w)
{
    edge[sign].to = v;
    edge[sign].w = w;
    edge[sign].next = first[u];
    first[u] = sign++;
    edge[sign].to = u;
    edge[sign].w = w;
    edge[sign].next = first[v];
    first[v] = sign++;
}
bool bfs(ll s, ll t)
{
    queue<ll> Q;
    memset(d, 0, sizeof(d));
    Q.push(s);
    d[s] = 1;
    while (Q.size())
    {
        int p = Q.front();
        Q.pop();
        for (ll i = first[p]; ~i; i = edge[i].next)
        {
            if (edge[i].w > 0 && d[edge[i].to] == 0)
            {
                d[edge[i].to] = d[p] + 1;
                if (edge[i].to == t)
                    return 1;
                Q.push(edge[i].to);
            }
        }
    }
    return d[t] != 0;
}
int zd[1010];
ll dfs(ll x, ll t, ll a)
{
    if (x == t || a == 0)
        return a;
    ll flow = 0, f;
    for (ll &i = cur[x]; ~i; i = edge[i].next)
    {
        if (d[x] + 1 == d[edge[i].to] && edge[i].w > 0)
        {
            f = dfs(edge[i].to, t, min(a - flow, edge[i].w));
            edge[i].w -= f;
            edge[i ^ 1].w += f;
            flow += f;
            if (edge[i].w)
                cur[x] = i;
            if (flow == a)
                break;
        }
    }
    if (flow == 0)
        d[x] = 0;
    return flow;
}
ll Dinic(int s, int t)
{
    ll flow = 0;
    while (bfs(s, t))
    {
        for (int i = 0; i <= n; i++)
            cur[i] = first[i];
        flow += dfs(s, t, inf);
    }
    return flow;
}
void wr(ll x)
{
    if (x < 0)
        putchar('-'), x = -x;
    if (x > 9)
        wr(x / 10);
    putchar(x % 10 + 48);
}
int got[5] = {1, -1, 0, 0, 0};
bool check(int x, int y)
{
    if (x > 0 && x <= n && y > 0 && y <= m)
        return true;
    return false;
}
int uu[200010], vv[200010], ww[200010];
int main()
{
    n = read();
    m = read();
    for (int i = 1; i <= m; i++)
    {
        scanf("%d %d %d", &uu[i], &vv[i], &ww[i]);
    }
    for (int i = 1; i <= m; i++)
    {
        memset(first, -1, sizeof(first));
        sign = 0;
        st = uu[i];
        ed = vv[i];
        for (int j = 1; j <= m; j++)
        {
            if (ww[j] < ww[i])
            {
                add_edge(uu[j], vv[j], 1);
            }
        }
        printf("%lld ", Dinic(st, ed));
    }
    return 0;
}
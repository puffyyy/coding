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
#define ll long long
#define INF 0x3f3f3f3f3f
#define maxn 2010
#define maxm 100010

vector<int> to[maxn];
vector<ll> v[maxn];
struct node
{
    int next, to;
    ll val;
};
struct node e[maxm * 2];
int cnt = 1, head[maxn], v1[maxn], depth[maxn];
ll dist[maxn], c[maxn];
queue<int> q;
int n, m, s, t;
void add_edge(int x, int y, ll z)
{
    e[++cnt].to = y;
    e[cnt].next = head[x];
    e[cnt].val = z;
    head[x] = cnt;
}
//链式前向星

void spfa()
{
    for (register int i = 2; i <= n; i++)
        dist[i] = INF;         //dist数组
    memset(v1, 0, sizeof(v1)); //是否在队列中
    dist[1] = 0;
    v1[1] = 1;
    while (!q.empty())
        q.pop();
    q.push(1);
    while (q.size())
    {
        int x = q.front();
        q.pop();
        v1[x] = 0;
        for (int i = 0; i < to[x].size(); i++)
        {
            int y = to[x][i];
            ll z = v[x][i];
            if (dist[y] > dist[x] + z)
            {
                dist[y] = dist[x] + z;
                if (!v1[y])
                    q.push(y), v1[y] = 1;
            }
        }
    }
}

//spfa模板

int bfs()
{
    while (!q.empty())
    {
        q.pop();
    }
    memset(depth, 0, sizeof(depth));
    q.push(s);
    depth[s] = 1;
    while (!q.empty())
    {
        int x = q.front();
        q.pop();
        for (int i = head[x]; i; i = e[i].next)
        {
            int y = e[i].to;
            ll z = e[i].val;
            if (!depth[y] && e[i].val)
            {
                depth[y] = depth[x] + 1;
                q.push(y);
            }
        }
    }
    return depth[t];
}

ll dfs(int x, ll val)
{
    if (x == t)
        return val;
    ll ans = 0;
    for (int i = head[x]; i; i = e[i].next)
    {
        if (ans == val)
            return ans;
        int y = e[i].to;
        ll z = e[i].val;
        if (depth[y] == depth[x] + 1 && z > 0)
        {
            ll sum = dfs(y, min(val - ans, z));
            if (sum > 0)
            {
                ans += sum;
                e[i].val -= sum;
                e[i ^ 1].val += sum;
            }
        }
    }
    return ans;
}

inline ll dinic()
{
    ll sum = 0; //一定要加long long
    while (bfs())
    {
        ll x = 1;
        while (x)
        {
            x = dfs(s, INF);
            sum += x;
        }
    }
    return sum;
}

int main()
{
    cin >> n >> m;
    t = 2 * n + 1;
    int x, y;
    ll val;
    for (int i = 1; i <= m; i++)
    {
        cin >> x >> y >> val;
        to[x].push_back(y);
        v[x].push_back(val);
        to[y].push_back(x);
        v[y].push_back(val);
    }
    spfa();
    for (int i = 1; i <= n; i++)
    {
        cin >> c[i];
    }
    add_edge(s, 1, INF);
    add_edge(1, s, 0);
    add_edge(2 * n, t, INF);
    add_edge(t, 2 * n, 0);
    for (int i = 1; i <= n; i++)
    {
        if (i != 1 && i != n)
        {
            add_edge(i, i + n, c[i]);
            add_edge(i + n, i, 0);
        }
        else
        {
            add_edge(i, i + n, INF);
            add_edge(i + n, i, 0);
        }
    }
    for (int i = 1; i <= n; i++)
    {
        for (int j = 0; j < to[i].size(); j++)
        {
            int ver = to[i][j];
            val = v[i][j];
            if (dist[ver] == dist[i] + val)
            {
                add_edge(i + n, ver, INF);
                add_edge(ver, i + n, 0);
            }
        }
    }
    ll ans = dinic();
    cout << ans << endl;
}
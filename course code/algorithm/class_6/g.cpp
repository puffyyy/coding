#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <cstdlib>
#include <algorithm>
using namespace std;
typedef long long ll;
const int MS = 1e5 + 5;
struct edge
{
    int s, t, w, f;
    bool operator<(const edge &p) const
    {
        return w == p.w ? f < p.f : w < p.w;
    }
} edges[MS << 1];
int n, m, t;
int ans;
int parent[MS];
void initUF()
{
    for (int i = 0; i <= n; i++)
        parent[i] = -1;
}
int findUF(int x)
{
    int s, tmp;
    for (s = x; parent[s] >= 0; s = parent[s])
        ;
    while (s != x)
    {
        tmp = parent[x];
        parent[x] = s;
        x = tmp;
    }
    return s;
}
void unionUF(int R1, int R2)
{
    int r1 = findUF(R1), r2 = findUF(R2);
    int tmp = parent[r1] + parent[r2];
    if (parent[r1] > parent[r2])
    {
        parent[r1] = r2;
        parent[r2] = tmp;
    }
    else
    {
        parent[r2] = r1;
        parent[r1] = tmp;
    }
}
int kruskal()
{
    int sum = 0;
    int num = 0;
    int u, v;
    ans = 0;
    sort(edges, edges + m);
    initUF();
    for (int i = 0; i < m && num < n - 1; i++)
    {
        u = edges[i].s, v = edges[i].t;
        if (findUF(u) != findUF(v))
        {
            unionUF(u, v);
            ans += edges[i].w;
            ++num;
            if (edges[i].f == 0)
                ++sum;
        }
    }
    return sum;
}
int main()
{
    scanf("%d%d%d", &n, &m, &t);
    for (int i = 0; i < m; i++)
    {
        scanf("%d%d%d%d", &edges[i].s, &edges[i].t, &edges[i].w, &edges[i].f);
    }
    int l = -105, r = 105, mid;
    int at, anss;
    while (l <= r)
    {
        mid = ((l + r) >> 1);
        for (int i = 0; i < m; i++)
            if (edges[i].f == 0)
                edges[i].w += mid;
        at = kruskal();
        if (at < t)
            r = mid - 1;
        else
        {
            l = mid + 1;
            anss = ans - mid * t;
        }
        for (int i = 0; i < m; i++)
            if (edges[i].f == 0)
                edges[i].w -= mid;
    }
    printf("%d", anss);
    return 0;
}
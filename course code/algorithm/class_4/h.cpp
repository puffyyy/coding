#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#define maxm 500006
struct node
{
    int a, b, c;
} edges[maxm];
int visit[maxm], color[maxm];
int head[maxm], to[maxm], wei[maxm], next[maxm], e_num;
int n, m;
inline void add_directed_e(int u, int v, int w)
{
    to[e_num] = v;
    wei[e_num] = w;
    next[e_num] = head[u];
    head[u] = e_num;
    ++e_num;
}
inline void insert_undirected_e(int a, int b, int w)
{
    add_directed_e(a, b, w);
    add_directed_e(b, a, w);
}

bool dfs(int s, int col)
{
    visit[s] = 1;
    color[s] = col;
    int v;
    for (int i = head[s]; ~i; i = next[i])
    {
        v = to[i];
        if (!color[v])
        {
            if (!dfs(v, 3 - col))
                return false;
        }
        else if (color[v] == col)
            return false;
    }
    return true;
}
bool check(int w)
{
    memset(visit, 0, sizeof(visit));
    memset(head, -1, sizeof(head));
    memset(color, 0, sizeof(color));
    e_num = 0;
    for (int i = 1; i <= m; i++)
        if (edges[i].c > w)
            insert_undirected_e(edges[i].a, edges[i].b, edges[i].c);
    for (int i = 1; i <= n; i++)
        if (!visit[i])
            if (!dfs(i, 1))
                return false;
    return true;
}
int main()
{
    int l, mid;
    int r = -1;
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= m; i++)
    {
        scanf("%d%d%d", &edges[i].a, &edges[i].b, &edges[i].c);
        r = edges[i].c > r ? edges[i].c : r;
    }

    l = 0, r += 1;
    while (l < r)
    {
        mid = ((l + r) >> 1);
        if (check(mid))
            r = mid;
        else
            l = mid + 1;
    }
    printf("%d", l);
    return 0;
}
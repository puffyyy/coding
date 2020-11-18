#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <limits.h>
#define __max_INF__ LLONG_MAX
#define maxm 10000

long long gr[maxm][maxm], gf[maxm][maxm], g[maxm][maxm];
int path[maxm];
int visit[maxm];
void creatGraph(int n, int m)
{
    int s, e, w;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            // g[i][j] = ((i == j) ? 0 : __max_INF__);
            g[i][j] = __max_INF__;
    for (int i = 0; i < m; i++)
    {
        scanf("%d%d%d", &s, &e, &w);
        g[s][e] = w;
        // adjmatrix[e][s] = w;
    }
}
int dfs_visit(int source, int ver_num, int terminal, int deepth)
{
    visit[source] = 1;
    if (source == terminal)
    {
        path[deepth] = source;
        return deepth;
    }
    for (int i = 1; i <= ver_num; i++)
    {
        if (i != source && g[source][i] != __max_INF__ && visit[i] == 0)
        {
            path[deepth] = i;
            dfs_visit(i, ver_num, terminal, deepth + 1);
            path[deepth] = -1;
        }
    }
    return -1;
}
void maximum_flow(int n, int s, int t)
{
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
            gr[i][j] = g[i][j];
    }
    int len = -1;
    while ((len = dfs_visit(s, n, t, 1)) != -1)
    {
        long long minadd = __max_INF__;
        path[0] = s;
        for (int i = 0; i <= len; i++)
        {
            if (minadd > gr[path[i]][path[i + 1]])
                minadd = gr[path[i]][path[i + 1]];
        }
        for (int i = 0; i <= len; i++)
        {
            gf[path[i]][path[i + 1]] += minadd;
            gr[path[i]][path[i + 1]] -= minadd;
            gr[path[i + 1]][path[i]] += minadd;
            if (gr[path[i]][path[i + 1]] == 0)
                gr[path[i]][path[i + 1]] = __max_INF__;
        }
        memset(visit, 0, sizeof(int) * maxm);
    }
}
int main()
{
    long long ans = 0;
    int n, m, s, t;
    scanf("%d%d%d%d", &n, &m, &s, &t);
    creatGraph(n, m);
    maximum_flow(n, s, t);
    for (int i = 1; i <= n; i++)
    {
        if (gf[s][i] != __max_INF__ && i != s)
            ans += gf[s][i];
    }
    printf("%lld", ans);
    return 0;
}
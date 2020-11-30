#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#define maxn 100005
#define maxm 100005
int cnt; //n个点，m条边
int color[maxm];
int cntline, line[maxm];
struct Edge
{
    int v;
    struct Edge *next;
} edge[maxn]; //边集
struct Edge *ver[maxn], *p[maxn];
void init(int n)
{
    for (int i = 1; i <= n; i++)
    {
        ver[i] = (struct Edge *)malloc(sizeof(struct Edge));
        ver[i]->next = NULL;
        p[i] = ver[i];
    }
}
void add_edge(int u, int v) //加边:u起点，v终点，w边权
{
    struct Edge *q = (struct Edge *)malloc(sizeof(struct Edge));
    q->next = NULL;
    q->v = v;
    p[u]->next = q;
    p[u] = q;
}
void dfs(int s)
{
    color[s] = 1;
    struct Edge *q = ver[s]->next;
    for (; q != NULL; q = q->next)
    {
        if (color[q->v] == 0)
        {
            dfs(q->v);
        }
    }
}
void bfsall(int ver_num)
{
    for (int i = 1; i <= ver_num; i++)
    {
        if (color[i] == 0)
        {
            dfs(i);
            line[cntline++] = i;
        }
    }
}

int main()
{
    int n, m; //n个节点，m条边
    scanf("%d%d", &n, &m);
    int u, v;
    init(n);
    for (int i = 1; i <= m; i++)
    {
        scanf("%d%d", &u, &v);
        add_edge(u, v);
        add_edge(v, u);
    }
    bfsall(n);
    printf("%d\n", cntline - 1);
    for (int i = 0; i < cntline - 1; i++)
        printf("%d %d\n", line[i], line[i + 1]);
    return 0;
}

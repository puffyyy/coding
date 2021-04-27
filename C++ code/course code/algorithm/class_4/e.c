#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define MAXVER 1005
#define MAXEDGE 1100000
struct edge
{
    int start, end;
    double weight;
} edges[MAXEDGE];
double xx[MAXVER], yy[MAXVER];
int idpath[MAXVER];
int parent[MAXVER]; //并查集根节点

int cmp(const void *a, const void *b) //升序
{
    struct edge *c = (struct edge *)a;
    struct edge *d = (struct edge *)b;
    return c->weight - d->weight;
}
void initUF()
{
    for (int i = 0; i < MAXVER; i++)
        parent[i] = -1;
}
int findUF(int x)
{
    int s, tmp;
    for (s = x; parent[s] >= 0; s = parent[s]) //s<0 说明s为根节点
        ;                                      //循环结束后找到根 s
    while (s != x)                             //将s到x上的路径的根更改为s
    {
        tmp = parent[x];
        parent[x] = s;
        x = tmp;
    }
    return s;
}
void unionUF(int R1, int R2)
{
    int r1 = findUF(R1),
        r2 = findUF(R2);               //r1 为 R1 的根结点，r2 为 R2 的根结点
    int tmp = parent[r1] + parent[r2]; //两个集合结点个数之和(负数)
    //如果 R2 所在树结点个数 > R1 所在树结点个数(注意 parent[root]是负数)
    if (parent[r1] > parent[r2]) //优化方案――加权法则
    {
        parent[r1] = r2; //r1的根 为 r2
        parent[r2] = tmp;
    }
    else
    {
        parent[r2] = r1;
        parent[r1] = tmp;
    }
}
void kruskal(int numver, int numedges)
{
    qsort(edges, numedges, sizeof(struct edge), cmp);
    double sumweight = 0;
    int num = 0;
    int u, v;
    initUF();
    for (int i = 0; i < numedges; i++)
    {
        u = edges[i].start, v = edges[i].end;
        if (findUF(u) != findUF(v))
        {
            unionUF(u, v);
            sumweight += edges[i].weight;
            num++;
        }
        if (num >= numver - 1)
            break;
    }
    printf("%.3lf\n", sumweight);
}
int main()
{
    int numver;
    scanf("%d", &numver);
    double x, y;
    for (int i = 0; i < numver; i++)
    {
        scanf("%lf%lf", xx + i, yy + i);
    }
    int numedges = 0;
    for (int i = 0; i < numver; i++)
        for (int j = 0; j < numver; j++)
        {
            if (i != j)
            {
                edges[numedges].start = i, edges[numedges].end = j;
                edges[numedges].weight = sqrt((xx[i] - xx[j]) * (xx[i] - xx[j]) + (yy[i] - yy[j]) * (yy[i] - yy[j]));
                numedges++;
            }
        }
    kruskal(numver, numedges);

    return 0;
}
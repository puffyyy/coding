#include <stdio.h>
#include <stdlib.h>
#define MAXVER 10
#define MAXEDGE 45
struct edge
{
    int id, start, end, weight;
} edges[MAXEDGE];
int idpath[MAXVER];
int parent[MAXVER]; //并查集根节点
int cmp(const void *a, const void *b)
{
    struct edge *c = (struct edge *)a;
    struct edge *d = (struct edge *)b;
    return c->weight - d->weight;
}
void creatGraph(int numedges)
{
    int i, s, e, w;
    int id;
    for (i = 0; i < numedges; i++)
    {
        scanf("%d%d%d%d", &id, &s, &e, &w);
        edges[i].id = id, edges[i].start = s, edges[i].end = e, edges[i].weight = w;
    }
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
    //如果 R2 所在树结点个数 > R1 所在树结点个数(注意 parent[r1]是负数)
    if (parent[r1] > parent[r2]) //优化方案――加权法则
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
void kruskal(int numver, int numedges)
{
    qsort(edges, numedges, sizeof(struct edge), cmp);
    int sumweight = 0;
    int num = 0;
    int u, v;
    initUF();
    for (int i = 0; i < numedges; i++)
    {
        u = edges[i].start, v = edges[i].end;
        if (findUF(u) != findUF(v))
        {
            idpath[num] = edges[i].id;
            printf("%d %d %d %d\n", edges[i].id, u, v, edges[i].weight);
            unionUF(u, v);
            sumweight += edges[i].weight;
            num++;
        }
        if (num >= numver - 1)
            break;
    }
    printf("weight of MST is %d\n", sumweight);
}
int main()
{
    int numver, numedges;
    scanf("%d%d", &numver, &numedges);
    creatGraph(numedges);
    kruskal(numver, numedges);

    return 0;
}
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAXVER 10
#define INFINITY 2147483647
int vertex[MAXVER];
int weight[MAXVER][MAXVER]; //当图G中存在边(i,j)，则weights[i][j]为其权值，否则为一个INFINITY
int edges[MAXVER];          //存入生成的最小生成树的边，如 ：(i, edges[i]) 为最小生成树的一条边，应有n-1条边

void initMatrix(int edge[][MAXVER])
{
    for (int i = 0; i < MAXVER; i++)
        for (int j = 0; j < MAXVER; j++)
            edge[i][j] = INFINITY;
}
void creatGraph(int edge[][MAXVER], int vernum, int edgenum)
{
    initMatrix(edge);
    int s, e, w;
    while (edgenum--)
    {
        scanf("%d%d%d", &s, &e, &w);
        edge[s][e] = w;
        edge[e][s] = w;
    }
}
void prim(int weights[][MAXVER], int n, int src, int edges[])
{
    int minweight[MAXVER], min; //存放未确定为生成树的顶点i至已确定的生成树上顶点的边权重，minweight[i] = 0 表示其已确定为最小生成树顶点
    int i, j, k;
    for (i = 0; i < n; i++)
    {
        minweight[i] = weight[src][i];
        edges[i] = src;
    }
    minweight[src] = 0;
    for (i = 1; i < n; i++)
    {
        min = INFINITY;
        for (j = 0, k = 0; j < n; j++)
        {
            if (minweight[j] != 0 && min > minweight[j])
            {
                k = j;
                min = minweight[k];
            }
        }

        minweight[k] = 0;
        for (j = 0; j < n; j++)
        {
            if (minweight[j] != 0 && minweight[j] > weights[k][j])
            {
                minweight[j] = weights[k][j];
                edges[j] = k;
            }
        }
    }
}
int main()
{
    int vernum, edgenum; //7,9
    scanf("%d%d", &vernum, &edgenum);
    creatGraph(weight, vernum, edgenum);
    prim(weight, vernum, 0, edges);
    for (int i = 1; i < vernum; i++)
        printf("%d %d %d\n", i, edges[i], weight[i][edges[i]]);
    return 0;
}
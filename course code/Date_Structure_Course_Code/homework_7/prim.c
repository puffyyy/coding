#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define INT_MAX 2147483647
#define MAXSIZE 101
int edges[MAXSIZE];
int sumofweight = 0;
struct
{
    int id;
    int weight;
} adjmatrix[MAXSIZE][MAXSIZE];
int cmp(const void *a, const void *b)
{
    int *c = (int *)a;
    int *d = (int *)b;
    return *c - *d;
}
void creatGraph(int n, int m)
{
    int id, start, end, weight;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
        {
            adjmatrix[i][j].weight = INT_MAX;
            adjmatrix[i][j].id = 0;
        }
    for (int i = 0; i < m; i++)
    {
        scanf("%d%d%d%d", &id, &start, &end, &weight);
        adjmatrix[start][end].id = id, adjmatrix[start][end].weight = weight;
        adjmatrix[end][start].id = id, adjmatrix[end][start].weight = weight;
    }
}
void prim(int start, int n)
{
    int lowcost[MAXSIZE], i, j, v, minweight;
    for (i = 0; i < n; i++)
    {
        lowcost[i] = adjmatrix[i][start].weight;
        edges[i] = adjmatrix[i][start].id;
    }
    lowcost[start] = 0;
    for (i = 1; i < n; i++)
    {
        minweight = INT_MAX;
        for (j = 0; j < n; j++)
        {
            if (lowcost[j] && minweight > lowcost[j])
            {
                minweight = lowcost[j];
                v = j;
            }
        }
        sumofweight += minweight;
        lowcost[v] = 0;
        for (j = 0; j < n; j++)
        {
            if (lowcost[j] && lowcost[j] > adjmatrix[j][v].weight)
            {
                edges[j] = adjmatrix[j][v].id;
                lowcost[j] = adjmatrix[j][v].weight;
            }
        }
    }
}
int main()
{
    int n, m;
    scanf("%d%d", &n, &m);
    creatGraph(n, m);
    prim(0, n);
    qsort(edges + 1, n - 1, sizeof(int), cmp);
    printf("%d\n", sumofweight);
    for (int i = 1; i < n; i++)
        printf("%d ", edges[i]);
    return 0;
}
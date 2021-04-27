#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#define MAX_INT 0x3fffffff
#define MAXVER 100

int adjmatrix[MAXVER][MAXVER];
int path[MAXVER]; //最短路径数组含义为path[v]表示顶点v在最短路径上的直接前驱顶点,path[v1]=v2 即表示v1的前驱是v2
int minweight[MAXVER];
//顶点从 0 开始的
void creatGraphByEdge(int n, int m)
{
    int s, e, w;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            adjmatrix[i][j] = MAX_INT;
    for (int i = 0; i < m; i++)
    {
        scanf("%d%d%d", &s, &e, &w);
        adjmatrix[s][e] = w;
    }
}
int crearGraphByMatrix(int numver)
{
    for (int i = 0; i < numver; i++)
        for (int j = 0; j < numver; j++)
        {
            scanf("%d", &adjmatrix[i][j]);
        }
}
void printmatrix(int n)
{
    printf("邻接矩阵:\n");
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (adjmatrix[i][j] == MAX_INT)
                printf(" 无穷 ");
            else
                printf("%3d ", adjmatrix[i][j]);
        }
        putchar('\n');
    }
}
void printresult(int source, int n)
{
    for (int i = 0; i < n; i++)
    {
        int j = i;
        if (i == source)
            continue;
        else if (minweight[i] == MAX_INT)
            printf("%d has no path.\n", i);
        else
        {
            printf("%d", i);
            while (j != source)
            {
                printf("<-%d", path[j]);
                j = path[j];
            }
            printf("sum=%d", minweight[i]);
            putchar('\n');
        }
    }
}
void dijkstra(int source, int n)
{
    char vfound[MAXVER];
    for (int i = 0; i < MAXVER; i++)
    {
        minweight[i] = adjmatrix[source][i];
        vfound[i] = 0;
        path[i] = source; //当前以i为终点的最短路径的前驱为source
    }                     //init
    minweight[source] = 0;
    vfound[source] = 1;

    for (int i = 0; i < n - 1; i++)
    {
        int v, min = MAX_INT;
        for (int j = 0; j < n; j++) //找未访问过的最小路径的边
        {
            if (!vfound[j] && (min > minweight[j]))
            {
                min = minweight[j];
                v = j;
            }
        }
        vfound[v] = 1; //标记该顶点已经找到最短路径
        for (int j = 0; j < n; j++)
        {
            if (!vfound[j] && adjmatrix[v][j] != MAX_INT && (min + adjmatrix[v][j]) < minweight[j])
            {
                minweight[j] = min + adjmatrix[v][j];
                //更新minweight,判断从当前已选择节点v出发是否有更短路径
                path[j] = v; //更新前驱
            }
        }
    }
}
int main()
{
    int numver, numedge;
    scanf("%d%d", &numver, &numedge);
    creatGraph(numver, numedge);
    printmatrix(numver);
    dijkstra(0, numver);
    printresult(0, numver);
    return 0;
}
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#define MAX_INT 0x3fffffff
#define MAXVER 550

int adjmatrix[MAXVER][MAXVER];
int path[MAXVER]; //最短路径数组含义为path[v]表示顶点v在最短路径上的直接前驱顶点,path[v1]=v2 即表示v1的前驱是v2
int minweight[MAXVER];

int crearGraphByMatrix(int numver)
{
    for (int i = 0; i < numver; i++)
        for (int j = 0; j < numver; j++)
        {
            scanf("%d", &adjmatrix[i][j]);
        }
    return 1;
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
            if (!vfound[j] && min > minweight[j])
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
    int t;
    scanf("%d", &t);
    while (t--)
    {
        int numver, numedge;
        scanf("%d", &numver);
        crearGraphByMatrix(numver);
        dijkstra(0, numver);
        printf("%d\n", minweight[numver - 1]);
    }
    return 0;
}
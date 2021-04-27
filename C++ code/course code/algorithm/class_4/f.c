#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#define INF 0x7fffffff
#define MAXVER 220

int adjmatrix[MAXVER][MAXVER];
int distance[MAXVER][MAXVER];
int path[MAXVER][MAXVER]; //path[i][j]存储从i到j的第一个途经节点
void creatGraph(int n, int m)
{
    int s, e, w;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            adjmatrix[i][j] = ((i == j) ? 0 : INF);
    for (int i = 0; i < m; i++)
    {
        scanf("%d%d%d", &s, &e, &w);
        adjmatrix[s - 1][e - 1] = w;
        // adjmatrix[e][s] = w;
    }
}

void floyd(int numver)
{
    int i, j, k;
    for (i = 0; i < numver; i++)
        for (j = 0; j < numver; j++)
        {
            distance[i][j] = adjmatrix[i][j];
            path[i][j] = ((adjmatrix[i][j] == INF) ? -1 : j);
        }
    for (k = 0; k < numver; k++)
        for (i = 0; i < numver; i++)
            for (j = 0; j < numver; j++)
            {
                if (distance[i][k] != INF && distance[k][j] != INF && distance[i][j] > distance[i][k] + distance[k][j])
                {
                    distance[i][j] = distance[i][k] + distance[k][j];
                    // path[i][j] = path[i][k];
                    path[i][j] = path[i][k];
                }
            }
}
void printallpath(int n)
{
    int max = -1;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
        {
            if (i == j)
                continue;
            if (distance[i][j] != INF)
            {
                if (max < distance[i][j])
                    max = distance[i][j];
            }
        }
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
        {
            if (distance[i][j] == max)
                printf("%d %d\n", i + 1, j + 1);
        }
}
int main()
{
    int t;
    scanf("%d", &t);
    while (t--)
    {
        int numver, numedge;
        scanf("%d%d", &numver, &numedge);
        creatGraph(numver, numedge);
        floyd(numver);
        printallpath(numver);
    }
    return 0;
}
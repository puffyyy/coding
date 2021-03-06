//多源最短路
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#define INF 0x7fffffff
#define MAXVER 127

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
        adjmatrix[s][e] = w;
        adjmatrix[e][s] = w;
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
                    path[i][j] = path[i][k];
                }
            }
}
void pathprint(int start, int end)
{
    printf("from %d to %d ", start, end);
    printf("the distance is %d.", distance[start][end]);
    printf("----path : ");
    int x = start;
    while (x != end)
    {
        printf("%d->", x);
        x = path[x][end];
    }
    printf("%d\n", end);
}
void printallpath(int n)
{
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
        {
            if (i == j)
                continue;
            if (distance[i][j] != INF)
            {
                pathprint(i, j);
            }
            else
            {
                printf("from %d to %d ", i, j);
                printf("cannot reach!!!\n");
            }
        }
}
int main()
{
    int numver, numedge;
    scanf("%d%d", &numver, &numedge);
    creatGraph(numver, numedge);
    floyd(numver);
    printallpath(numver);
    //pathprint(0, 3);
    return 0;
}

//https://blog.csdn.net/weixin_39956356/java/article/details/80620667

//test
/*
5 
8 
0 1 50 
0 3 40 
0 4 25 
1 2 15 
1 3 20 
2 3 10 
2 4 20 
3 4 10 
*/
/*4 4 0 1 2 1 2 2 2 3 2 0 3 7*/
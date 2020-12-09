#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXVER 305
#define min(a, b) ((a) > (b) ? (b) : (a))
int adjmatrix[MAXVER][MAXVER];
int distance[MAXVER][MAXVER];
int dis2[MAXVER][MAXVER];
int a, b;
void floyd(int numver, int a, int b)
{
    int i, j, k;
    for (i = 0; i < numver; i++)
        for (j = 0; j < numver; j++)
        {
            distance[i][j] = dis2[i][j] = adjmatrix[i][j];
        }
    for (k = 0; k < numver; k++)
    {
        if (k == b)
            continue;
        for (i = 0; i < numver; i++)
        {
            if (i == b)
                continue;
            for (j = 0; j < numver; j++)
            {
                if (j == b)
                    continue;
                if (distance[i][j] > distance[i][k] + distance[k][j])
                {
                    distance[i][j] = distance[i][k] + distance[k][j];
                }
            }
        }
    }
    for (k = 0; k < numver; k++)
    {
        if (k == a)
            continue;
        for (i = 0; i < numver; i++)
        {
            if (i == a)
                continue;
            for (j = 0; j < numver; j++)
            {
                if (j == a)
                    continue;
                if (dis2[i][j] > dis2[i][k] + dis2[k][j])
                {
                    dis2[i][j] = dis2[i][k] + dis2[k][j];
                }
            }
        }
    }
}
void printallpath(int n)
{
    for (int i = 0; i < n; i++)
    {
        if (i == a || i == b)
            continue;
        for (int j = 0; j < n; j++)
        {
            if (j == a || j == b)
                continue;
            printf("%d ", min(distance[i][j], dis2[i][j]));
        }
        putchar('\n');
    }
}
int main()
{
    int numver;
    while (~scanf("%d", &numver))
    {
        for (int i = 0; i < numver; i++)
            for (int j = 0; j < numver; j++)
                scanf("%d", &adjmatrix[i][j]);
        scanf("%d%d", &a, &b);
        a--, b--;
        floyd(numver, a, b);
        printallpath(numver);
        putchar('\n');
    }
    return 0;
}

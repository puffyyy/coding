#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#define maxm 100
int matrix[maxm][maxm];
int dis[maxm];
int pre[maxm];
void bellman_ford(int vernum, int source)
{
    for (int i = 1; i <= vernum; i++)
    {
        pre[i] = -1;
        dis[i] = 0x3fffffff;
    }
    dis[source] = 0;
    for (int i = 1; i < vernum; i++)
    {
        for (int j = 1; j <= vernum; j++)
        {
            for (int k = 1; k <= vernum; k++) //对于每条边
                if (j != k && matrix[j][k] != 0)
                {
                    if (dis[k] > dis[j] + matrix[j][k]) //判断能否 relax
                    {
                        dis[k] = dis[j] + matrix[j][k];
                        pre[k] = j;
                    }
                }
        }
    }

    //judge
}
int judge_minus(int vernum)
{
    for (int j = 1; j <= vernum; j++)
        for (int k = 1; k <= vernum; k++) //对于每条边
            if (j != k && matrix[j][k] != 0)
                if (dis[k] > dis[j] + matrix[j][k]) //判断能否 relax
                    return 1;                       // 有负环
    return 0;
}
int main()
{

    int n;
    int source;
    scanf("%d%d", &n, &source);
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            scanf("%d", &matrix[i][j]);
    bellman_ford(n, source);
    if (judge_minus(n))
        printf("error! negative loop");
    else
    {
        for (int i = 1; i <= n; i++)
            printf("%d ", dis[i]);
    }
    return 0;
}
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#define typec int // type of cost
#define SIZE 1000
const typec inf = 0x3f3f3f3f; // max of cost
int vis[SIZE];
typec lowcost[SIZE];
typec cost[SIZE][SIZE];
typec prim(int n) // vertex: 0 ~ n-1
{
    int i, j, p;
    typec minc, res = 0;
    memset(vis, 0, sizeof(vis));
    vis[0] = 1;
    for (i = 1; i < n; i++)
        lowcost[i] = cost[0][i];
    for (i = 1; i < n; i++)
    {
        minc = inf;
        p = -1; //下一个节点
        for (j = 0; j < n; j++)
            if (0 == vis[j] && minc > lowcost[j])
            {
                minc = lowcost[j];
                p = j;
            }
        if (inf == minc)
            return -1; // 原图不连通
        res += minc;
        vis[p] = 1;
        for (j = 0; j < n; j++)
            if (0 == vis[j] && lowcost[j] > cost[p][j])
                lowcost[j] = cost[p][j];
    }
    return res;
}
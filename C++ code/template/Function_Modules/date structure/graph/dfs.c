#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#define maxm 100
int ver[maxm], color[maxm], d[maxm], f[maxm], pre[maxm];
int a[maxm][maxm];
int time;
void dfs_visit(int start, int ver_num)
{
    time++;
    d[start] = time;
    color[start] = 1;
    for (int i = 1; i <= ver_num; i++)
    {
        if (i != start && color[i] == 0)
        {
            pre[i] = start;
            dfs_visit(i, ver_num);
        }
    }
    color[start] = 2;
    time++;
    f[start] = time;
}
void dfs(int ver_num)
{
    for (int i = 1; i <= ver_num; i++)
    {
        color[i] = 0;
        pre[i] = -1;
    }
    time = 0;
    for (int i = 1; i <= ver_num; i++)
    {
        if (color[i] == 0)
            dfs_visit(i, ver_num);
    }
}

int main()
{
    int n, m; //n个节点，m条边
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
            scanf("%d", &a[i][j]);
    }
    dfs(n);
    for (int i = 1; i <= n; i++)
        printf("%d ", d[i]);
    return 0;
}

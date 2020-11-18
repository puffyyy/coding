#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#define maxm 100
int dis[maxm], vis[maxm]; //vis 表示是否在队列中
int q[maxm * 2];
int a[maxm][maxm];
void spfa(int n, int s) //求含负权边的单源最短路径
{
    for (int i = 0; i <= n; i++)
        dis[i] = 0x3fffffff; //初始化每点i到s的距离
    dis[s] = 0;
    vis[s] = 1;
    q[1] = s; // 队列初始化, s为起点
    int i, v, head = 0, tail = 1;
    while (head < tail) //队列非空
    {
        head++;
        v = q[head];             //取队首元素
        vis[v] = 0;              // 释放队首结点，因为这节点可能下次用来松弛其它节点，重新入队
        for (i = 0; i <= n; i++) //对所有顶点
            if (a[v][i] > 0 && dis[i] > dis[v] + a[v][i])
            {
                dis[i] = dis[v] + a[v][i]; //修改最短路
                if (vis[i] == 0)           // 如果扩展结点i不在队列中，入队
                {
                    tail++;
                    q[tail] = i;
                    vis[i] = 1;
                }
            }
    }
}

int main()
{

    return 0;
}
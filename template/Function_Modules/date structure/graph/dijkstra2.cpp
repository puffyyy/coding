//链表 dijkstra 未堆优化
#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include <stack>
#include <queue>
#include <set>
using namespace std;
typedef long long ll;
const int inf = 0x7fffffff;
const int MS = 5e6 + 5;
const int maxn = 100005;
int cnt;
struct Edge
{
	int to, w, next; //终点，边权，同起点的上一条边的编号
} edge[MS];			 //边集 搞大点
int head[maxn];		 //head[i],表示以i为起点的第一条边在边集数组的位置（编号）
void init(int n)
{ //初始化
	//	for (int i = 0; i <= n; i++)head[i] = -1;
	memset(head, -1, sizeof(head));
	cnt = 0;
}
void add_edge(int u, int v, int w)
{
	edge[cnt].to = v;
	edge[cnt].w = w;
	edge[cnt].next = head[u];
	head[u] = cnt;
	++cnt;
}
char visit[maxn];
int minweight[maxn];
void dijkstra(int source, int n)
{
	memset(visit, 0, sizeof(char) * maxn);
	for (int i = 1; i <= n; i++)
	{
		minweight[i] = inf;
	}
	for (int i = head[source]; ~i; i = edge[i].next)
	{
		minweight[edge[i].to] = min(edge[i].w, minweight[edge[i].to]);
	}
	minweight[source] = 0;
	visit[source] = 1;
	for (int i = 0; i < n - 1; i++)
	{
		int min = inf;
		int v;
		for (int j = 1; j <= n; j++)
		{ //找未访问过的最小路径的边
			if (!visit[j] && (min > minweight[j]))
			{
				min = minweight[j];
				v = j;
			}
		}
		visit[v] = 1; //标记该顶点已经找到最短路径
		for (int j = head[v]; ~j; j = edge[j].next)
		{
			if (!visit[edge[j].to] && min + edge[j].w < minweight[edge[j].to])
			{
				minweight[edge[j].to] = min + edge[j].w;
			}
		}
	}
}
int main()
{
	int n, m, s;
	scanf("%d%d%d", &n, &m, &s);
	int u, v, w;
	init(n);
	for (int i = 1; i <= m; i++)
	{
		scanf("%d%d%d", &u, &v, &w);
		add_edge(u, v, w);
	}
	dijkstra(s, n);
	for (int i = 1; i <= n; i++)
		printf("%d ", minweight[i]);
	return 0;
}
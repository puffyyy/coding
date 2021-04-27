////链表 dijkstra 堆优化 nlogn
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
int cnt; //n个点，m条边
struct Edge
{
	int to, w, next; //终点，边权，同起点的上一条边的编号
} edge[MS];			 //边集 搞大点
int head[maxn];		 //head[i],表示以i为起点的第一条边在边集数组的位置（编号）
void init(int n)
{ //初始化
	//	for (int i = 0; i <= n; i++)
	//		head[i] = -1;
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
int dis[maxn];
void dijk(int s, int n) // source  vernum
{
	memset(visit, 0, sizeof(visit));
	priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> que; //小顶堆 >
	for (int i = 1; i <= n; i++)
		dis[i] = inf;
	dis[s] = 0; //初始化dis数组
	que.push(make_pair(0, s));
	while (que.size()) //当堆中还有元素
	{
		int x = que.top().second; //q.top()取出堆顶，也就是当前距离起点最近的点。
		que.pop();				  //取完就删
		if (visit[x])
			continue; //如果这个定点标记过了，就不用。
		visit[x] = 1; //标记一下
		for (int i = head[x]; ~i; i = edge[i].next)
		{
			if (dis[edge[i].to] > dis[x] + edge[i].w) //dijkstra算法核心语句
			{
				dis[edge[i].to] = dis[x] + edge[i].w;
				que.push(make_pair(dis[edge[i].to], edge[i].to)); //每次松弛成功，把关于当前点的信息压入堆。
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
	dijk(s, n);
	for (int i = 1; i <= n; i++)
		printf("%d ", dis[i]);
	return 0;
}
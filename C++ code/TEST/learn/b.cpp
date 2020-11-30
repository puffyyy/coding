#include <cstdio>
#include <iostream>
#include <cstring>
#include <queue>
using namespace std;
#define maxn 1000005
#define maxm 1000005
int cnt; //n个点，m条边
struct Edge
{
    int to, next; //终点，边权，同起点的上一条边的编号
} edge[maxn];     //边集
int head[maxn];   //head[i],表示以i为起点的第一条边在边集数组的位置（编号）
int color[maxm];
int cntline, line[maxm];
void initlist(int n) //初始化
{
    memset(color, 0, sizeof(color));
    memset(head, -1, sizeof(head));
    cnt = 0;
    cntline = 0;
}
void add_edge(int u, int v) //加边:u起点，v终点，w边权
{
    edge[cnt].to = v;
    edge[cnt].next = head[u];
    head[u] = cnt++;
}
void bfs(int start)
{
    queue<int> que;
    color[start] = 1;
    que.push(start);
    int u;
    while (!que.empty())
    {
        u = que.front(), que.pop();
        for (int j = head[u]; j != -1; j = edge[j].next) //遍历以i为起点的边
        {
            if (color[edge[j].to] == 0)
            {
                color[edge[j].to] = 1;
                que.push(edge[j].to);
            }
        }
    }
}
void dfs(int s)
{
    color[s] = 1;
    for (int j = head[s]; j != -1; j = edge[j].next) //遍历以i为起点的边
    {
        if (color[edge[j].to] == 0)
        {
            dfs(edge[j].to);
        }
    }
}
void bfsall(int ver_num)
{
    for (int i = 1; i <= ver_num; i++)
    {
        if (color[i] == 0)
        {
            dfs(i);
            line[cntline++] = i;
        }
    }
}
int main()
{
    int n, m; //n个节点，m条边
    cin >> n >> m;
    int u, v;
    initlist(n);
    for (int i = 1; i <= m; i++)
    {
        cin >> u >> v;
        add_edge(u, v);
        add_edge(v, u);
    }
    bfsall(n);
    cout << cntline - 1 << endl;
    for (int i = 0; i < cntline - 1; i++)
        cout << line[i] << " " << line[i + 1] << endl;

    return 0;
}

//链式前向星
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
const int MS = 1e5 + 5;
const int maxn = 1005;
int n, m, cnt; //n个点，m条边
struct Edge
{
    int to, w, next; //终点，边权，同起点的上一条边的编号
} edge[maxn];        //边集
int head[maxn];      //head[i],表示以i为起点的第一条边在边集数组的位置（编号）
void init()          //初始化
{
    for (int i = 0; i <= n; i++)
        head[i] = -1;
    //memset(head,-1,sizeof(head));
    cnt = 0;
}
void add_edge(int u, int v, int w) //加边:u起点，v终点，w边权
{
    edge[cnt].to = v;
    edge[cnt].w = w;
    edge[cnt].next = head[u];
    head[u] = cnt;
    ++cnt;
}
int main()
{
    cin >> n >> m;
    int u, v, w;
    init();                      //初始化
    for (int i = 1; i <= m; i++) //输入m条边
    {
        cin >> u >> v >> w;
        add_edge(u, v, w); //加边
        /*
        加双向边
        add_edge(u, v, w);
        add_edge(v, u, w);
        */
    }
    for (int i = 1; i <= n; i++) //n个起点
    {
        cout << i << endl;
        for (int j = head[i]; j != -1; j = edge[j].next) //遍历以i为起点的边
        {
            cout << i << " " << edge[j].to << " " << edge[j].w << endl;
        }
        cout << endl;
    }
    return 0;
}

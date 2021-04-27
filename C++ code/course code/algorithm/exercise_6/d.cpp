#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <cstdlib>
#include <algorithm>
#include <queue>
using namespace std;
typedef long long ll;
const int maxn = 1005;
int n, m, cnt; //n个点，m条边
struct Edge
{
    int to, next;  //终点，边权，同起点的上一条边的编号
} edge[maxn << 2]; //边集 搞大点
int head[maxn];    //head[i],表示以i为起点的第一条边在边集数组的位置（编号）
int ver[maxn];
int visit[maxn];
int cntorder = 0;
void init() //初始化
{
    memset(head, -1, sizeof(head));
    cnt = 0;
}
void add_edge(int u, int v) //加边:u起点，v终点，w边权
{
    edge[cnt].to = v;
    edge[cnt].next = head[u];
    head[u] = cnt;
    ++cnt;
}
bool IsSquare(int num)
{
    int m = int(sqrt(num) + 0.5);
    if (m * m == num)
        return true;
    return false;
}
void judge()
{
    for (int i = 1; i <= n; i++)
    {
        for (int j = i + 1; j <= n; j++)
        {
            if (IsSquare((ver[i] + ver[j])))
            {
                add_edge(i, j);
                add_edge(j, i);
            }
        }
    }
}
int bfs(int start)
{
    memset(visit, 0, sizeof(visit));
    queue<int> que;
    visit[start] = 1;
    que.push(start);
    int u;
    while (!que.empty())
    {
        u = que.front(), que.pop();
        for (int j = head[u]; j != -1; j = edge[j].next) //遍历以i为起点的边
        {
            if (visit[edge[j].to] == 0)
            {
                visit[edge[j].to] = 1;
                que.push(edge[j].to);
            }
        }
    }
    for (int i = 1; i <= n; i++)
        if (visit[i] == 0)
            return 0;
    return 1;
}
void dfs(int s, int deepth)
{
    if (deepth == n)
    {
        cntorder++;
        return;
    }
    for (int j = head[s]; j != -1; j = edge[j].next) //遍历以i为起点的边
    {
        if (visit[edge[j].to] == 0)
        {
            visit[edge[j].to] = 1;
            dfs(edge[j].to, deepth + 1);
            visit[edge[j].to] = 0;
        }
    }
}
int main()
{
    int div = 1, k = 1;
    cin >> n;
    init();
    for (int i = 1; i <= n; i++)
        cin >> ver[i];
    sort(ver + 1, ver + n + 1);
    judge();

    if (bfs(1))
    {
        if (ver[1] == ver[n])
        {
            cout << "1";
            return 0;
        }
        if (n >= 2 && ver[1] == ver[n - 1] && ver[1] != ver[n])
        {
            cout << n;
            return 0;
        }
        if (n >= 3 && ver[1] == ver[n - 2] && ver[1] != ver[n] && ver[1] != ver[n - 1])
        {
            if (IsSquare(ver[n - 1] + ver[n]))
            {
                if (IsSquare(ver[1] + ver[n - 1]) && !IsSquare(ver[1] + ver[n]))
                {
                    cout << "1";
                    return 0;
                }
                else if (IsSquare(ver[1] + ver[n - 1]) && IsSquare(ver[1] + ver[n]))
                {
                    if (ver[n - 1] != ver[n])
                        cout << (n - 1) * n;
                    else
                        cout << (n - 1) * n / 2;
                    return 0;
                }
                else if (!IsSquare(ver[1] + ver[n - 1]) && IsSquare(ver[1] + ver[n]))
                {
                    cout << "1";
                    return 0;
                }
            }
            else
            {
                if (ver[n - 1] == ver[n])
                    cout << "1";
                else
                    cout << "2";
                return 0;
            }
        }
        for (int i = 1; i <= n; i++)
        {
            memset(visit, 0, sizeof(visit));
            visit[i] = 1;
            dfs(i, 1);
            visit[i] = 0;
        }

        for (int i = 2; i <= n; i++)
        {
            if (ver[i] == ver[i - 1])
            {
                k++;
                div *= k;
            }
            else
                k = 1;
        }
    }
    cout << cntorder / div;
    return 0;
}
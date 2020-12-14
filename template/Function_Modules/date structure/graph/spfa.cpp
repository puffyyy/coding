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
#define inf 0x3f3f3f3f3f3f3f3f
const int VER = 550;
vector<int> to[VER];
vector<int> val[VER]; // ll
ll dis[VER];
void spfa(int n, int s)
{
    int u, v, w;
    int visit[VER];
    queue<int> que;
    memset(visit, 0, sizeof(visit));
    for (int i = 1; i <= n; i++)
        dis[i] = inf;
    dis[s] = 0, visit[s] = 1;
    que.push(s);

    while (que.size())
    {
        u = que.front(), que.pop();
        visit[u] = 0;
        for (int i = 0; i < to[u].size(); i++)
        {
            v = to[u][i];
            w = val[u][i];
            if (dis[v] > dis[u] + w)
            {
                dis[v] = dis[u] + w;
                if (!visit[v])
                    que.push(v), visit[v] = 1;
            }
        }
    }
}
int main()
{
    int n, m;
    scanf("%d%d", &n, &m);
    int a, b, v;
    for (int i = 0; i < m; i++)
    {
        scanf("%d%d%d", &a, &b, &v);
        to[a].push_back(b);
        val[a].push_back(v);
        to[b].push_back(a);
        val[b].push_back(v);
    }
    spfa(n, 1);
    return 0;
}

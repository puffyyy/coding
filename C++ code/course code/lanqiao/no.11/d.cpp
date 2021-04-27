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
int root[10];
int find(int x)
{
    int u = x;
    for (; root[u] > 0; u = root[u])
        ;
    int tmp;
    while (u != x)
    {
        tmp = root[x];
        root[x] = u;
        x = root[x];
    }
    return u;
}

int map[10][10];
int visit[10];
int ans;
void dfs(int x)
{

    if (x > 7)
    {
        for (int i = 1; i <= 7; i++)
            root[i] = -1;
        for (int i = 1; i <= 7; i++)
        {
            for (int j = 1; j <= 7; j++)
            {
                if (map[i][j] == 1 && visit[i] && visit[j])
                    if (find(i) != find(j))
                    {
                        root[i] = find(j);
                    }
            }
        }
        int cnt = 0;
        for (int i = 1; i <= 7; i++)
        {
            if (root[i] == -1 && visit[i])
                cnt++;
        }
        if (cnt == 1)
            ans++;
        return;
    }
    visit[x] = 1;
    dfs(x + 1);
    visit[x] = 0;
    dfs(x + 1);
}
int main()
{
    //ios::sync_with_stdio(false);
    //cin.tie(nullptr);
    map[1][2] = map[2][1] = 1;
    map[1][6] = map[6][1] = 1; //连通的存图
    map[6][7] = map[7][6] = 1;
    map[6][5] = map[5][6] = 1;
    map[2][7] = map[7][2] = 1;
    map[2][3] = map[3][2] = 1;
    map[5][7] = map[7][5] = 1;
    map[5][4] = map[4][5] = 1;
    map[3][7] = map[7][3] = 1;
    map[4][3] = map[3][4] = 1;
    dfs(1);
    printf("%d", ans);
    return 0;
}
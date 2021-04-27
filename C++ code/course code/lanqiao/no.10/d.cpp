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
int map[60][60];
int vis[60][60];
int m[4][2] = {
    0,
    1,
    -1,
    0,
    1, 0,
    0, -1}; //0 x 1 y

string s[4] = {"D", "L", "R", "U"};
int hx, hy;
string bfs()
{
    queue<pair<pair<int, int>, string>> que;
    que.push(make_pair(make_pair(1, 1), ""));
    vis[1][1] = 1;
    pair<int, int> p;
    int x, y;
    string tmp;
    int xx, yy;
    while (!que.empty())
    {
        p = que.front().first, tmp = que.front().second;
        que.pop();
        x = p.first, y = p.second;
        if (x == hx && y == hy)
            return tmp;
        for (int i = 0; i < 4; i++)
        {
            xx = x + m[i][0], yy = y + m[i][1];
            if (xx > 0 && yy > 0 && xx <= hx && yy <= hy && vis[yy][xx] == 0 && map[yy][xx] == 0)
            {
                vis[yy][xx] = 1;
                que.push(make_pair(make_pair(xx, yy), tmp + s[i]));
            }
        }
    }
}

int main()
{
    //ios::sync_with_stdio(false);
    //cin.tie(nullptr);
    // for (int i = 0; i < 4; i++)
    //     for (int j = 0; j < 2; j++)
    //         cout << m[i][j] << " ";
    hx = 50, hy = 30;
    string t;
    for (int i = 1; i <= hy; i++)
    {
        cin >> t;
        for (int j = 1; j <= hx; j++)
            map[i][j] = t[j - 1] - '0';
    }
    cout << bfs();

    return 0;
}
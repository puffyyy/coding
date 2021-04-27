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
const int MS = 305;
int c[MS], d[MS], dis[MS];
int dp[MS][MS];
int main()
{
    int n, t;
    scanf("%d%d", &n, &t);
    t *= 12;
    int m = t, ans = 0;
    for (int i = 1; i <= n; i++)
        scanf("%d", c + i);
    for (int i = 1; i <= n; i++)
        scanf("%d", d + i);
    for (int i = 2; i <= n; i++)
        scanf("%d", dis + i);
    for (int i = 0; i <= n; ++i)
        for (int j = 0; j <= t; ++j)
            dp[i][j] = -0x3f3f3f3f;
    dp[0][0] = 0;
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= t; j++)
        {
            for (int k = 0; k + dis[i] <= j && (k - 1) * d[i] < c[i]; k++)
                dp[i][j] = max(dp[i][j], dp[i - 1][j - dis[i] - k] + (c[i] + c[i] - (k - 1) * d[i]) * k / 2);
            ans = max(ans, dp[i][j]);
        }
    }
    printf("%d", ans);
    return 0;
}

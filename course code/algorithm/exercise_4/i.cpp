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
#define mod 100000007
typedef long long ll;
const int MS = 1e3 + 5;
int i, n, k;
int a[MS];
int dp[MS][MS];
int main()
{
    scanf("%d%d", &n, &k);
    for (i = 1; i <= n; ++i)
        scanf("%d", a + i);
    sort(a + 1, a + n + 1);
    int e = (a[n] - a[1]) / (k - 1) + 1;
    int before_i;
    int ans = 0;
    a[0] = -mod;
    for (int x = 1; x < e; ++x)
    {
        before_i = 0;
        for (i = 1; i <= n; ++i)
        {
            while (a[i] - a[before_i] >= x)
                ++before_i;
            --before_i;
            dp[i][2] = (dp[i - 1][2] + before_i);
            if (dp[i][2] >= mod)
                dp[i][2] -= mod;
            for (int j = 3; j <= k && j <= i; ++j)
            {
                dp[i][j] = dp[i - 1][j] + dp[before_i][j - 1];
                if (dp[i][j] >= mod)
                    dp[i][j] -= mod;
            }
        }
        ans += dp[n][k];
        if (ans >= mod)
            ans -= mod;
    }
    printf("%d", ans);
    return 0;
}
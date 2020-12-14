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
const int MS = 3e3 + 5;
ll a[MS];
ll dp[MS][MS];
int main()
{
    //ios::sync_with_stdio(false);
    //cin.tie(nullptr);
    int n;
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
    {
        scanf("%lld", a + i);
    }
    for (int l = n; l >= 1; l--)
    {
        for (int i = 1; i + l - 1 <= n; i++)
        {
            int j = i + l - 1;
            dp[i][j] = max(dp[i - 1][j] + a[i] * (n - l + 1), dp[i][j + 1] + a[j] * (n - l + 1));
        }
    }
    ll ans = 0;
    for (int i = 1; i <= n; i++)
    {
        ans = max(ans, dp[i][i]);
    }
    printf("%lld", ans);
    return 0;
}
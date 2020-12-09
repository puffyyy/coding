#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long ll;
const int MS = 1e3 + 5;
ll dp[MS][2];
int a[MS], n, k;
int main()
{
    while (~scanf("%d%d", &n, &k))
    {
        memset(dp, 0, sizeof(dp));
        for (int i = 1; i <= n; i++)
            scanf("%d", &a[i]);
        if (k > n / 2)
        {
            ll ans = 0;
            for (int i = 2; i <= n; ++i)
                ans += max(0, a[i] - a[i - 1]);
            printf("%lld\n", ans);
            continue;
        }
        for (int j = 1; j <= k; j++)
            dp[j][1] -= a[1];
        for (int i = 2; i <= n; i++)
            for (int j = k; j > 0; j--)
            {
                dp[j][0] = max(dp[j][0], dp[j][1] + a[i]);
                dp[j][1] = max(dp[j][1], dp[j - 1][0] - a[i]);
            }
        printf("%lld\n", dp[k][0]);
    }
    return 0;
}
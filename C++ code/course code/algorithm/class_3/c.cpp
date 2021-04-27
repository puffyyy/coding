#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <cstdlib>
#include <algorithm>
#include <limits.h>
using namespace std;
typedef long long ll;
const int MS = 1e3 + 5;
ll a[MS];
ll dp[MS][MS];
int main()
{
    //ios::sync_with_stdio(false);
    //cin.tie(nullptr);
    ll n;
    scanf("%lld", &n);
    for (ll i = 1; i <= n; i++) //2*n -1
    {
        scanf("%lld", a + i);
        a[i + n] = a[i];
    }
    for (ll i = 1; i <= 2 * n - 1; i++)
        dp[i][i] = 0;
    ll j, q;
    for (ll l = 2; l <= n; l++)
    {
        for (ll i = 1; i <= 2 * n - l; i++)
        {
            j = i + l - 1;
            dp[i][j] = LLONG_MAX;
            for (ll k = j - 1; k >= i; k--)
            {
                q = dp[i][k] + dp[k + 1][j] + a[i] * a[k + 1] * a[j + 1];
                if (q < dp[i][j])
                {
                    dp[i][j] = q;
                }
            }
        }
    }
    ll ans = LLONG_MAX;
    for (ll i = 1; i <= n; i++)
    {
        ans = min(dp[i][i + n - 1], ans);
    }
    printf("%lld", ans);
    return 0;
}
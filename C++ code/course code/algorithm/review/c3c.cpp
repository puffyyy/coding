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
const int MS = 805;
ll a[MS];
ll dp[MS][MS];
int main()
{

    int n;
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
    {
        scanf("%lld", a + i);
        a[i + n] = a[i];
    }
    ll ans = 2147483131453647;
    for (int l = 2; l <= n; l++)
    {
        for (int i = 1; i <= n * 2 - l; i++)
        {
            int j = i + l - 1;
            ll tmp = 2147483131453647;
            dp[i][j] = 2147483131453647;
            for (int k = i; k < j; k++)
                tmp = min(tmp, dp[i][k] + dp[k + 1][j] + a[i] * a[k + 1] * a[j + 1]);
            dp[i][j] = tmp;
        }
    }
    for (int i = 1; i <= n; i++)
    {
        ans = min(dp[i][i + n - 1], ans);
    }

    printf("%lld", ans);
    return 0;
}
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
const int MS = 1e3 + 5;
ll dp[MS][MS];
ll a[MS];

int main()
{
    //ios::sync_with_stdio(false);
    //cin.tie(nullptr);
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++)
        cin >> a[i];
    for (int len = n - 2; len >= 0; len--)
    {
        for (int i = 1; i <= n - len; i++)
        {
            int r = i + len;
            dp[i][r] = max(dp[i - 1][r] + a[i - 1] * (n - len - 1), dp[i][r + 1] + a[r + 1] * (n - len - 1));
        }
    }
    ll ans = 0;
    for (int i = 1; i <= n; i++)
        ans = max(dp[i][i] + n * a[i], ans);
    cout << ans;
    return 0;
}
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
typedef long long int ll;
const int MS = 1e5 + 5;
int mat[81][81];
__int128 dp[81][81];
inline void output(__int128 x)
{
    if (x > 9)
        output(x / 10);
    putchar(x % 10 + '0');
}
int main()
{
    ios::sync_with_stdio(false);
    int n, m;
    cin >> n >> m;
    __int128 ans = 0;
    for (int i = 1; i <= n; ++i)
    {
        for (int j = 1; j <= m; ++j)
            cin >> mat[i][j];
    }
    for (int i = 1; i <= n; ++i)
    {
        memset(dp, 0, sizeof(dp));
        for (int len = 0; len <= m; len++)
            for (int j = 1; j <= m - len; j++)
            {
                dp[j][j + len] = 2 * max(dp[j + 1][j + len] + mat[i][j], dp[j][j + len - 1] + mat[i][j + len]);
            }
        ans += dp[1][m];
    }
    output(ans);
    return 0;
}
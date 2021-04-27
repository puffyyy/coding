#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <cstdlib>
#include <algorithm>
#define mod 1000000007
using namespace std;
int a[54][10008];
int dp[54][10008];
int main()
{
    int t, n, m;
    scanf("%d", &t);
    while (t--)
    {
        scanf("%d%d", &n, &m);
        int ans;
        for (int i = 1; i <= n; ++i)
        {
            for (int j = 1; j <= m; ++j)
                scanf("%d", a[i] + j);
            sort(a[i] + 1, a[i] + 1 + m);
        }
        for (int j = 1; j <= m; ++j)
            dp[n][j] = 1;
        for (int i = n - 1; i > 0; --i)
        {
            int sum_j = 0;
            int k = 1;
            ans = -1;
            for (int j = 1; j <= m; ++j)
            {
                while (dp[i + 1][k] == 0 && k <= m)
                    ++k;
                while (a[i][j] >= a[i + 1][k] && k <= m)
                {
                    sum_j += dp[i + 1][k++];
                    sum_j -= (sum_j >= mod ? mod : 0);
                    ans = 0;
                }
                dp[i][j] = sum_j;
            }
        }
        if (~ans)
            for (int j = 1; j <= m; ++j)
            {
                ans += dp[1][j];
                ans -= (ans >= mod ? mod : 0);
            }
        printf("%d\n", ans);
    }
    return 0;
}
/*
3
3 3
2 1 0 
0 0 3
2 1 3 
*/

#include <cstdio>
#include <cstring>
using namespace std;
int a[55];
long long dp[55][1001];
int main()
{
    int t, n;
    scanf("%d", &t);
    while (t--)
    {
        int cnt = 0;
        scanf("%d", &n);
        memset(dp, 0, sizeof(dp));
        for (int i = 1; i <= n; i++)
            scanf("%d", a + i);
        // dp[0][0] = 1;
        for (int i = 0; i <= n; i++)
            dp[i][0] = 1;
        for (int i = 1; i <= n; i++)
        {
            for (int j = 1; j <= 1000; j++)
                if (j >= a[i])
                    dp[i][j] = dp[i - 1][j] + dp[i - 1][j - a[i]];
                else
                    dp[i][j] = dp[i - 1][j];
        }

        for (int j = 1; j <= 1000; j++)
            if (dp[n][j] > 0)
                cnt++;

        printf("%d\n", cnt);
    }
    return 0;
}
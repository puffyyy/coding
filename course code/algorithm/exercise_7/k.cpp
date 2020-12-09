#include <iostream>
#include <cstdio>
using namespace std;
typedef long long ll;
const int mod = 1e9 + 7;
const int MS = 1e3 + 5;
ll dp[MS][MS];
int main()
{
    int t, x, y;
    scanf("%d", &t);
    while (t--)
    {
        scanf("%d%d", &x, &y);
        if (x < y * 2)
        {
            printf("-1\n");
            continue;
        }
        if (dp[x][y])
        {
            printf("%lld\n", dp[x][y]);
            continue;
        }
        for (int i = 0; i <= x; i++)
            for (int j = 0; j <= i / 2; j++)
            {
                if (j == 0)
                    dp[i][j] = 1;
                else
                    dp[i][j] = (dp[i][j - 1] + dp[i - 1][j]) % mod;
            }
        printf("%lld\n", dp[x][y]);
    }
    return 0;
}
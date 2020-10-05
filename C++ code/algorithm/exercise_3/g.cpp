#include <cstdio>
#include <cmath>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;
typedef long long int ll;
const int MS = 1e5 + 1;
int a[MS];
int main()
{

    int n, m;
    scanf("%d%d", &n, &m);
    int **dp = (int **)new int *[n + 1];
    for (int i = 0; i <= n; i++)
    {
        dp[i] = new int[m + 1];
        memset(dp[i], 0, sizeof(int) * (m + 1));
    }
    for (int i = 1; i <= n; ++i)
    {
        scanf("%d", &a[i]);
        dp[i][1] = dp[i - 1][1] + a[i];
    }
    int min_ij, tmp_ij;
    for (int i = 1; i <= n; ++i) //前 i 长度
    {
        for (int j = 2; j <= m; ++j) //分为 j 段
        {
            min_ij = 0x7fffffff;
            for (int k = 1; k <= i; ++k)
            {
                tmp_ij = max(dp[k][j - 1], dp[i][1] - dp[k][1]);
                if (tmp_ij < min_ij)
                    min_ij = tmp_ij;
            }
            dp[i][j] = min_ij;
        }
    }
    printf("%d\n", dp[n][m]);
    return 0;
}
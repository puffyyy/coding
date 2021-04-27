#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <cstdlib>
#include <algorithm>
using namespace std;
typedef long long ll;
const int MS = 3e2 + 5;
int a[MS], b[MS], t[MS];
int dp[MS][MS], c[MS];
int n, m;
int main()
{
    scanf("%d%d", &n, &m);
    m *= 12;
    for (int i = 1; i <= n; i++)
        scanf("%d", a + i);
    for (int i = 1; i <= n; i++)
        scanf("%d", b + i);
    for (int i = 2; i <= n; i++)
        scanf("%d", t + i);
    // dp[i][j] 从n湖到达j湖 在j湖的时间为i 所得到的价值
    for (int j = n; j >= 1; j--) // 1 ~ j lake
    {
        for (int i = 1, cnt = 0; i <= m; ++i, ++cnt) // list c
            c[i] = c[i - 1] + ((a[j] - cnt * b[j]) > 0 ? (a[j] - cnt * b[j]) : 0);
        for (int i = 1; i <= m; i++) //time
        {
            dp[i][j] = c[i];
            if (i > t[j + 1])
                for (int k = 0; k <= i - t[j + 1]; k++)
                    if (dp[i][j] < dp[i - t[j + 1] - k][j + 1] + c[k])
                        dp[i][j] = dp[i - t[j + 1] - k][j + 1] + c[k];
        }
    }
    printf("%d", dp[m][1]);
    return 0;
}
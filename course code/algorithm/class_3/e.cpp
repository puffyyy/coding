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
int a[MS], b[MS], dp[MS][MS], w[MS][MS];

int main()
{
    //ios::sync_with_stdio(false);
    //cin.tie(nullptr);
    int n;
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
    {
        scanf("%d", a + i);
    }
    for (int i = 0; i <= n; i++)
    {
        scanf("%d", b + i);
    }
    for (int i = 1; i <= n + 1; i++)
    {
        dp[i][i - 1] = b[i - 1];
        w[i][i - 1] = b[i - 1];
    }
    int j, t;
    for (int l = 1; l <= n; l++)
    {
        for (int i = 1; i <= n - l + 1; i++)
        {
            j = i + l - 1;
            dp[i][j] = 2147483640;
            w[i][j] = w[i][j - 1] + a[j] + b[j];
            for (int r = i; r <= j; r++)
            {
                t = dp[i][r - 1] + dp[r + 1][j] + w[i][j];
                if (t < dp[i][j])
                    dp[i][j] = t;
            }
        }
    }
    printf("%d", dp[1][n]);
    return 0;
}
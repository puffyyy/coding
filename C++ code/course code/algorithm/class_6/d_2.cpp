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
int dp[MS][MS];
int a[MS][MS];
int T, n, m;
int main()
{
    scanf("%d", &T);
    while (T--)
    {
        scanf("%d%d", &n, &m);
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= m; j++)
                scanf("%d", &a[i][j]);
        memset(dp, 0, sizeof(dp));
        for (int i = 1; i <= n; i++)
            for (int j = m; j > 0; j--)
            {
                dp[i][j] = max(dp[i - 1][j + 1] + a[i][j], max(dp[i - 1][j], dp[i][j + 1]));
            }
        printf("%d\n", dp[n][1]);
    }
    return 0;
}
/*
#include <iostream>
#include <cstdio>
#include <cstring>
#define max(a, b) (a > b ? a : b)
using namespace std;
typedef long long ll;
const int MS = 1e3 + 5;
int a[MS][MS];
int T, n, m;
int main()
{
    scanf("%d", &T);
    while (T--)
    {
        memset(a, 0, sizeof(a));
        scanf("%d%d", &n, &m);
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= m; j++)
                scanf("%d", &a[i][j]);
        for (int i = 1; i <= n; i++)
            for (int j = m; j > 0; j--)
            {
                a[i][j] = max(a[i - 1][j + 1] + a[i][j], max(a[i - 1][j], a[i][j + 1]));
            }
        printf("%d\n", a[n][1]);
    }
    return 0;
}
*/
#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;
const int MS = 1e5 + 5;
int a[MS];
int map[MS];
int dp[MS];
int len, b;
int main()
{
    int n;
    scanf("%d", &n);
    register int i;
    for (i = 1; i <= n; ++i)
    {
        scanf("%d", a + i);
        map[a[i]] = i;
        dp[i] = MS;
    }
    for (i = 1; i <= n; ++i)
    {
        scanf("%d", &b);
        if (map[b] > dp[len])
            dp[++len] = map[b];
        else
        {
            int pos = upper_bound(dp, dp + len, map[b]) - dp;
            dp[pos] = map[b];
        }
    }
    printf("%d", len);
    return 0;
}
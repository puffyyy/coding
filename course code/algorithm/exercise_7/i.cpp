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
const int MS = 1e5 + 5;
ll dp[MS];
struct node
{
    int c, w, n;
} a[505];
int n, V;
int main()
{
    while (~scanf("%d%d", &n, &V))
    {
        memset(dp, 0, sizeof(dp));
        for (int i = 1; i <= n; i++)
        {
            scanf("%d%d%d", &a[i].c, &a[i].w, &a[i].n);
        }
        for (int i = 1; i <= n; i++)
        {
            if (a[i].n == 233 || a[i].c * a[i].n > V)
            {
                for (int j = a[i].c; j <= V; j++)
                    dp[j] = max(dp[j - a[i].c] + a[i].w, dp[j]);
            }
            else
            {
                int k = 1;
                int remaincnt = a[i].n;
                while (k < remaincnt)
                {
                    for (int j = V; j >= k * a[i].c; j--)
                    {
                        dp[j] = max(dp[j], dp[j - k * a[i].c] + k * a[i].w);
                    }
                    remaincnt -= k;
                    k <<= 1;
                }
                for (int j = V; j >= remaincnt * a[i].c; j--)
                {
                    dp[j] = max(dp[j], dp[j - remaincnt * a[i].c] + remaincnt * a[i].w);
                }
            }
        }
        printf("%lld\n", dp[V]);
    }
    return 0;
}
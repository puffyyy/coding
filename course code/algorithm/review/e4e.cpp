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
const int MS = 550;
int n, v;
int w[MS], p[MS], c[MS];
int dp[30008];
int main()
{
    register int i;
    while (scanf("%d%d", &n, &v) != EOF)
    {
        memset(dp, 0, sizeof(dp));
        for (i = 1; i <= n; i++)
            scanf("%d%d%d", w + i, p + i, c + i);
        for (i = 1; i <= n; i++)
        {
            if (w[i] * c[i] >= v)
                for (int j = w[i]; j <= v; j++)
                    dp[j] = max(dp[j], dp[j - w[i]] + p[i]);
            else
            {
                int remain_cnt = c[i];
                int k = 1;
                while (k <= remain_cnt)
                {
                    for (int j = v; j >= k * w[i]; j--)
                        dp[j] = max(dp[j], dp[j - k * w[i]] + k * p[i]);
                    remain_cnt -= k;
                    k *= 2;
                }
                for (int j = v; j >= remain_cnt * w[i]; j--)
                    dp[j] = max(dp[j], dp[j - remain_cnt * w[i]] + remain_cnt * p[i]);
            }
        }
        printf("%d\n", dp[v]);
    }
    return 0;
}
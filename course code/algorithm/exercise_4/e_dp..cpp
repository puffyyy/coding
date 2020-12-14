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
typedef long long int ll;
const int MS = 550;
int dp[30005];
int w[MS];
int price[MS];
int cnt[MS];
int main()
{
    int n, v;
    while (~scanf("%d%d", &n, &v))
    {
        memset(dp, 0, sizeof(dp));
        for (int i = 0; i < n; i++)
            scanf("%d%d%d", w + i, price + i, cnt + i);
        for (int i = 0; i < n; i++)
        {
            if (w[i] * cnt[i] > v)
                for (int j = w[i]; j <= v; j++)
                {
                    dp[j] = max(dp[j], dp[j - w[i]] + price[i]);
                }
            else
            {
                int k = 1;
                int remaincnt = cnt[i];
                while (k < remaincnt)
                {
                    for (int j = v; j >= k * w[i]; j--)
                    {
                        dp[j] = max(dp[j], dp[j - k * w[i]] + k * price[i]);
                    }
                    remaincnt -= k;
                    k <<= 1;
                }
                for (int j = v; j > remaincnt * w[i]; j--)
                {
                    dp[j] = max(dp[j], dp[j - remaincnt * w[i]] + remaincnt * price[i]);
                }
            }
        }
        printf("%d\n", dp[v]);
    }
    return 0;
}
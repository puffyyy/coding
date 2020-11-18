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
struct node
{
    ll w;
    ll v;
} p[MS];
ll dp[11000];
int main()
{
    int t;
    scanf("%d", &t);
    int n, k;
    while (t--)
    {
        memset(dp, 0, sizeof(dp));
        int flag = 0;
        scanf("%d%d", &n, &k);
        for (int i = 0; i < k; i++)
        {
            scanf("%lld%lld", &p[i].v, &p[i].w);
            if (p[i].w == 0 && p[i].v != 0)
                flag = 1;
        }
        if (flag == 1)
        {
            printf("Gua Sha Zhi Wang!\n");
            continue;
        }
        for (int i = 0; i < k; i++)
            for (int j = p[i].w; j < n; j++)
            {
                dp[j] = max(dp[j], dp[j - p[i].w] + p[i].v);
            }
        ll tmp = 0, ans = 0;
        for (int i = 0; i < n; i++)
        {
            if (dp[tmp] < dp[i])
                tmp = i;
        }
        ans += dp[tmp];
        tmp = 0;
        for (int i = 0; i < k; i++)
        {
            if (tmp < p[i].v)
                tmp = p[i].v;
        }
        ans += tmp;
        printf("%lld\n", ans);
    }
    return 0;
}
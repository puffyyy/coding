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
#define mod 1000000007
const int MS = 1e5 + 5;
int box[51][10005];
int dp[51][10005];
int main()
{
    int t, n, m;
    register int i, j, k;
    scanf("%d", &t);
    while (t--)
    {
        memset(dp, 0, sizeof(dp));
        scanf("%d%d", &n, &m);
        for (i = 0; i < n; ++i)
        {
            for (j = 0; j < m; ++j)
                scanf("%d", &box[i][j]);
            sort(box[i], box[i] + m);
        }

        for (j = 0; j < m; ++j)
            dp[n - 1][j] = 1;
        ll tmpans = 0;
        int pre;
        int flag;
        for (i = n - 2; i >= 0; --i)
        {
            tmpans = pre = j = flag = 0;
            while (pre < m && j < m)
            {
                if (dp[i + 1][pre] == 0)
                {
                    ++pre;
                    continue;
                }
                if (box[i + 1][pre] <= box[i][j])
                {
                    tmpans += dp[i + 1][pre++];
                    if (tmpans >= mod)
                        tmpans -= mod;
                    flag = 1;
                }
                else
                    dp[i][j++] = tmpans;
            }
            while (j < m)
                dp[i][j++] = tmpans;
            if (!flag)
                break;
        }
        if (!flag)
        {
            printf("-1\n");
            continue;
        }
        ll ans = 0;
        for (j = 0; j < m; ++j)
            ans = (ans + dp[0][j]) % mod;
        printf("%d\n", ans);
    }
    return 0;
}
/*
3
3 3
2 1 0 
0 0 3
2 1 3 
*/

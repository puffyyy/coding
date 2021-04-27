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
const int MS = 1e5 + 5;
int a[MS], b[MS];
int dp[2][MS];
int main()
{
    // ios::sync_with_stdio(false);
    int n;
    scanf("%d", &n);
    register int i, j;
    for (i = 1; i <= n; ++i)
        scanf("%d", a + i);
    for (i = 1; i <= n; ++i)
        scanf("%d", b + i);

    int cur = 1, pre = 0;
    for (i = 1; i <= n; ++i)
    {
        for (j = 1; j <= n; ++j)
        {
            if (a[i] == b[j])
                dp[cur][j] = dp[pre][j - 1] + 1;
            else
                dp[cur][j] = max(dp[pre][j], dp[cur][j - 1]);
        }
        swap(cur, pre);
    }
    printf("%d", dp[pre][n]);
    return 0;
}
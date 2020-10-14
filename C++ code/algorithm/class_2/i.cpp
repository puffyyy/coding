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
int cnt[MS];
int dp[MS];
int main()
{
    //ios::sync_with_stdio(false);
    int n, tmp, ma = -1;
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &tmp);
        ++cnt[tmp];
        if (ma < tmp)
            ma = tmp;
    }
    dp[1] = cnt[1];
    dp[2] = cnt[2] << 1;
    for (int i = 3; i <= ma; i++)
    {
        dp[i] = max(dp[i - 2] + i * cnt[i], dp[i - 1]);
    }
    printf("%d", dp[ma]);
    return 0;
}
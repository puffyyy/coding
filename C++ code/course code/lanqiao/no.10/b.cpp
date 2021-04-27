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
const int MS = 3e7 + 5;
int dp[MS] = {0, 1, 1, 1, 3};
int f(int x)
{
    for (int i = 4; i <= x; i++)
    {
        dp[i] = (dp[i - 1] + dp[i - 2] + dp[i - 3]) % 10000;
    }
    return dp[x];
}
int main()
{
    //ios::sync_with_stdio(false);
    //cin.tie(nullptr);

    cout << f(20190324);
    for (int i = 3; i <= 100000; i++)
    {
        for (int j = 3; j < i; j++)
        {
            {
                if (dp[i] == dp[j] && dp[i + 1] == dp[j + 1] && dp[i + 2] == dp[j + 2])
                {
                    printf("i=%d j=%d", i, j);
                    return 0;
                }
            }
        }
    }
    return 0;
}
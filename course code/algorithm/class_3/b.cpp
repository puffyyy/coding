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
int a[MS];
int dp[MS];

int main()
{
    //ios::sync_with_stdio(false);
    //cin.tie(nullptr);
    int n;
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%d", a + i);
    dp[0] = 0;
    int q;
    for (int j = 1; j <= n; j++)
    {
        q = -2147483648;
        for (int i = 1; i <= j; i++)
        {
            if (q < a[i] + dp[j - i])
            {
                q = a[i] + dp[j - i];
            }
        }
        dp[j] = q;
    }
    printf("%d", dp[n]);
    return 0;
}
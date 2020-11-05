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
int n;
int a[MS];
int dp[MS][MS];
int s[MS][MS];
void print(int i, int j)
{
    if (i == j)
        printf("A%d", i);
    else
    {
        printf("(");
        print(i, s[i][j]);
        print(s[i][j] + 1, j);
        printf(")");
    }
}
int main()
{
    while (~scanf("%d", &n))
    {
        for (int i = 0; i <= n; i++)
            scanf("%d", a + i);
        for (int i = 1; i <= n; i++)
            dp[i][i] = 0;
        int j, q;
        // n -= 1;
        for (int l = 2; l <= n; l++)
        {
            for (int i = 1; i <= n - l + 1; i++)
            {
                j = i + l - 1;
                dp[i][j] = 214748364;
                for (int k = j - 1; k >= i; k--)
                {
                    q = dp[i][k] + dp[k + 1][j] + a[i - 1] * a[k] * a[j];
                    if (q < dp[i][j])
                    {
                        dp[i][j] = q;
                        s[i][j] = k;
                    }
                }
            }
        }
        printf("%d\n", dp[1][n]);
        print(1, n);
        putchar('\n');
    }
    return 0;
}
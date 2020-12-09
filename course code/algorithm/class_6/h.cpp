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
int n, mod, dp[302][303], ans[303], sum1[303], C[303][303];
ll q_mul(int a, int b, int p) //(a*b)%p
{
    unsigned long long c = (long double)a / p * b;
    ll ret = (unsigned long long)a * b - (unsigned long long)c * p;
    ret %= p;
    if (ret < 0)
        ret += p;
    return ret % p;
}
long long quick_mul(long long x, long long y, long long mod)
{
    long long ans = 0;
    while (y != 0)
    {
        if (y & 1)
            ans += x, ans %= mod;
        x = x + x, x %= mod;
        y >>= 1;
    }
    return ans;
}
int main()
{
    scanf("%d %d", &n, &mod);
    for (int i = 0; i <= n; i++)
        C[i][0] = 1;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= i; j++)
            C[i][j] = (C[i - 1][j] + C[i - 1][j - 1]) % mod;
    printf("0");
    dp[1][1] = 1;
    for (int i = 2; i <= n; i++)
    {
        dp[1][i] = 1; //每一次只有一个数的情况 我们都要补上现在这个数结尾的方案
        for (int k = 2; k <= n; k++)
        {
            for (int j = 1; j <= i; j++)
                sum1[j] = (sum1[j - 1] + dp[k - 1][j]) % mod; //维护前缀和
            for (int j = 1; j <= i; j++)
            {
                if (!(k & 1))
                    dp[k][j] = sum1[j - 1];
                else
                    dp[k][j] = (sum1[i] - sum1[j]) % mod;
            }
        }
        for (int j = 1; j <= i; j++)
            ans[i] = (ans[i] + dp[n][j]) % mod;
        for (int j = 1; j < i; j++)
            ans[i] = (ans[i] - quick_mul(ans[j], C[i][j], mod)) % mod;
        while (ans[i] < 0)
            ans[i] += mod;
        printf(" %d", ans[i]);
    }
    return 0;
}
#include <stdio.h>
#include <stdlib.h>
long long binarypow(int a, int n)
{
    if (n == 0)
        return 1;
    else if (n & 1)
        return a * binarypow(a, n - 1);
    else
    {
        long long ans = binarypow(a, n >> 1);
        return ans * ans;
    }
}
long long quickpow(int a, int n)
{
    long long ans = 1;
    while (n > 0)
    {
        if (n & 1)
            ans *= a;
        a *= a;
        n >>= 1;
    }
    return ans;
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
long long q_mul(int a, int b, int p) //(a*b)%p
{
    unsigned long long c = (long double)a / p * b;
    long long ret = (unsigned long long)a * b - (unsigned long long)c * p;
    ret %= p;
    if (ret < 0)
        ret += p;
    return ret % p;
}
long long quick_pow(long long x, long long y, long long mod)
{
    long long ans = 1;
    while (y != 0)
    {
        if (y & 1)
            ans = quick_mul(ans, x, mod) % mod;
        x = quick_mul(x, x, mod), x %= mod;
        y = y >> 1;
    }
    return ans;
}
int main()
{
    printf("%lld", quickpow(5, 2));
    return 0;
}
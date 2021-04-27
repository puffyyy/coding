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
const long long n = 1001733993063167141;
const long long d = 212353;
const long long C = 20190324;
const ll p = 891234941;
const ll q = 1123984201;
// const ll i_temp = 140300;
ll e = 823816093931522017;
// x*a+y*b=gcd(a,b)
void Ex_gcd(long long a, long long b, long long &x, long long &y)
{
    if (b == 0)
    {
        x = 1;
        y = 0;
        return;
    }
    long long x1, y1;
    Ex_gcd(b, a % b, x1, y1);
    x = y1;
    y = x1 - (a / b) * y1;
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
long long quick_pow(long long x, long long y, long long mod)
{
    long long ans = 1;
    while (y != 0)
    {
        if (y & 1)
            ans = quick_mul(ans, x, mod);
        x = quick_mul(x, x, mod);
        y = y >> 1;
    }
    return ans;
}
int main()
{
    ll mul = (p - 1) * (q - 1);
    ll u, uu;
    Ex_gcd(d, mul, u, uu);
    u = (u + mul) % mul;
    printf("%lld\n", u);

    ll ans2 = quick_pow(C, e, n);
    printf("%lld", ans2);
    // e=823816093931522017
    // ans=579706994112328949
    return 0;
}
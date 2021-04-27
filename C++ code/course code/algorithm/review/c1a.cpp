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
const ll MS = 1e5 + 15;
ll a[MS];
ll tree[MS];
ll n;
ll b[MS];
ll lowbit(ll x)
{
    return x & (-x);
}
void update(ll x, ll k)
{
    while (x <= n + 5)
    {
        tree[x] += k;
        x += lowbit(x);
    }
    return;
}
ll query(ll x) //[1-x]
{
    ll ret = 0;
    while (x > 0)
    {
        ret += tree[x];
        x -= lowbit(x);
    }
    return ret;
}
int main()
{
    scanf("%lld", &n);
    for (ll i = 1; i <= n; i++)
    {
        scanf("%d", a + i);
        b[i] = a[i];
    }
    sort(b + 1, b + 1 + n);
    ll ans = 0;
    for (ll i = n; i >= 1; i--)
    {
        ll pos = lower_bound(b + 1, b + 1 + n, a[i]) - b + 2;
        ans += query(pos - 1);
        update(pos, 1);
    }
    printf("%lld\n", ans);
    return 0;
}
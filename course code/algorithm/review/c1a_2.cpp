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
ll ans;
int n;
int a[MS];
int temp[MS];
ll merge(int ll, int lr, int rl, int rr)
{
    if (ll == rr)
        return 0;
    long long ans = 0;
    int pos = ll;
    int l = ll, r = rr;
    while (ll <= lr && rl <= rr)
    {
        if (a[ll] <= a[rl])
            temp[pos++] = a[ll++];
        else
        {
            temp[pos++] = a[rl++];
            ans += lr - ll + 1;
        }
    }
    while (ll <= lr)
    {
        temp[pos++] = a[ll++];
    }
    while (rl <= rr)
        temp[pos++] = a[rl++];
    for (int i = l; i <= r; i++)
        a[i] = temp[i];
    return ans;
}
ll mergesort(int l, int r)
{
    if (r <= l)
        return 0;
    int mid = (l + r) / 2;
    ll ans = 0;
    ans += mergesort(l, mid);
    ans += mergesort(mid + 1, r);
    ans += merge(l, mid, mid + 1, r);
    return ans;
}
int main()
{
    scanf("%lld", &n);
    for (ll i = 1; i <= n; i++)
    {
        scanf("%d", a + i);
    }
    printf("%lld\n", mergesort(1, n));
    // for (ll i = 1; i <= n; i++)
    // {
    //     printf("%d ", a[i]);
    // }
    return 0;
}
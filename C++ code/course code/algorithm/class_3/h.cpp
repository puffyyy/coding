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
const ll MS = 1e5 + 5;
struct node
{
    ll cnt;
    ll val;
} jewel[MS];
bool cmp(node &a, node &b)
{
    return a.val > b.val;
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    ll n, v;
    cin >> n >> v;
    for (ll i = 1; i <= n; i++)
    {
        cin >> jewel[i].cnt >> jewel[i].val;
    }
    sort(jewel + 1, jewel + n + 1, cmp);
    ll ans = 0;
    for (ll i = 1; i <= n && v > 0; i++)
    {
        if (jewel[i].cnt >= v)
        {
            ans += v * jewel[i].val;
            v = 0;
        }
        else
        {
            v -= jewel[i].cnt;
            ans += jewel[i].cnt * jewel[i].val;
        }
    }
    cout << ans;
    return 0;
}
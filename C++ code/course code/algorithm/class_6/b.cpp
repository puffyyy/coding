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
#define sqr(x) ((x) * (x))
const int MS = 1e5 + 5;
ll gcd(ll a, ll b)
{
    ll c;
    while (a % b != 0)
    {
        c = a;
        a = b;
        b = c % b;
    }
    return b;
}
ll cnt_point_on(ll vx, ll vy)
{

    if (vy == 0)
        return vx - 1;
    if (vx == 0)
        return vy - 1;
    return gcd(max(vx, vy), min(vx, vy)) - 1;
}
int main()
{
    //ios::sync_with_stdio(false);
    //cin.tie(nullptr);
    int t;
    cin >> t;
    while (t--)
    {
        ll ax, ay, bx, by, cx, cy;
        ll ans;
        cin >> ax >> ay >> bx >> by >> cx >> cy;
        ll v1x = bx - ax, v1y = by - ay;
        ll v2x = cx - ax, v2y = cy - ay;
        ll v3x = bx - cx, v3y = by - cy;
        ll s = abs(v1x * v2y - v1y * v2x) / 2;
        ll cnt = 3;
        cnt += cnt_point_on(abs(v1x), abs(v1y));
        cnt += cnt_point_on(abs(v2x), abs(v2y));
        cnt += cnt_point_on(abs(v3x), abs(v3y));
        cnt /= 2;
        ans = s + 1 - cnt;
        cout << ans << endl;
    }
    return 0;
}
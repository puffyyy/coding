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
string str[8] = {"Awesome!\n", "Awful!\n"};
struct Vec
{
    ll x, y;
    Vec(ll xx = 0, ll yy = 0)
    {
        x = xx, y = yy;
    }
};
inline ll dot_product(const Vec &a, const Vec &b)
{
    return a.x * b.x + a.y * b.y;
}
inline ll cross_product(const Vec &a, const Vec &b) //a 在 b 的顺时针
{
    return a.x * b.y - a.y * b.x;
}
inline ll judge(const Vec &a, const Vec &b)
{
    ll c = cross_product(a, b);
    ll d = dot_product(a, b);
    if (c == 0 && d > 0)
        return 0;
    else
        return 1;
}
int main()
{
    ll t;
    scanf("%lld\n", &t);
    ll x, y, a, b;
    while (t--)
    {
        scanf("(%lld, %lld) (%lld, %lld)\n", &x, &y, &a, &b);
        cout << str[judge(Vec(x, y), Vec(a, b))];
    }
    return 0;
}
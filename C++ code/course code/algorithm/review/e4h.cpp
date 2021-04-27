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
int dp[12][10][2][2][2][2][2]; //要填的位 前一位 前一位与再前一位是否相同 有无三连 有无8 有无4 上限
int num[12];
ll recur(int p, int pre, bool same, bool _3, bool _8, bool _4, bool limit)
{
    if (_4 && _8)
        return 0;
    if (p == 0)
        return _3;
    if (~dp[p][pre][same][_3][_8][_4][limit])
        return dp[p][pre][same][_3][_8][_4][limit];
    int upper = limit ? num[p] : 9;
    ll ret = 0;
    for (int i = 0; i <= upper; i++)
        ret += recur(p - 1, i, i == pre, (same && i == pre) || _3, _8 || (i == 8), _4 || (i == 4), limit && (i == num[p]));
    dp[p][pre][same][_3][_8][_4][limit] = ret;
    return ret;
}
ll solve(ll x)
{
    if (x < 1e10)
        return 0;
    memset(dp, -1, sizeof(dp));
    int len;
    for (len = 0; x; x /= 10)
        num[++len] = x % 10;
    ll ret = 0;
    for (int i = 1; i <= num[len]; i++)
        ret += recur(10, i, 0, 0, i == 8, i == 4, i == num[len]);
    return ret;
}
int main()
{
    ll a, b;
    scanf("%lld%lld", &a, &b);
    printf("%lld", solve(b) - solve(a - 1));
    return 0;
}
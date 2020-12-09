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
int m, n;

ll a[MS];

int check(double x)
{
    int cnt = 1;
    ll left = a[1];
    double right = a[1] + x * 2;
    for (int i = 2; i <= n; i++)
    {
        if (right > a[i] - 1e-6)
            continue;
        else
        {
            left = a[i];
            right = left + 2 * x;
            ++cnt;
        }
    }
    if (cnt > m)
        return -1;
    else if (cnt == m)
        return 0;
    else
        return 1;
}

int main()
{
    //ios::sync_with_stdio(false);
    //cin.tie(nullptr);
    scanf("%d%d", &m, &n);
    for (int i = 1; i <= n; i++)
    {
        scanf("%lld", &a[i]);
    }
    sort(a + 1, a + n + 1);
    double target = 0;
    double left = 0, right = a[n] - a[1] + 8;
    double mid;
    while (right - left > 0.01) //终止条件是 left == right 左闭右开
    {
        mid = left + (right - left) / 2;
        if (check(mid) >= 0)
        {
            right = mid;
        }
        else
        {
            left = mid;
        }
    }
    printf("%.1lf", mid + 0.00001);
    return 0;
}
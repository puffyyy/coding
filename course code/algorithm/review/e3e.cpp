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
const int MS = 1e6 + 5;
int tree[MS];
int sum[MS], b[MS];
int high[MS], low[MS];
int n, x, y;
inline int lowbit(int x) { return x & (-x); }
int query(int x)
{
    int ans = 0;
    while (x > 0)
    {
        ans += tree[x];
        x -= lowbit(x);
    }
    return ans;
}
void add(int x)
{
    while (x <= n + 5)
    {
        ++tree[x];
        x += lowbit(x);
    }
    return;
}

int main()
{
    cin >> n >> x >> y;
    if (x > y)
        swap(x, y);
    int a;
    for (int i = 1; i <= n; i++)
    {
        cin >> a;
        sum[i] = sum[i - 1] + a;
        b[i] = sum[i], high[i] = sum[i] - x, low[i] = sum[i] - y;
    }
    sort(b, b + n);
    for (int i = 0; i <= n; i++)
    {
        sum[i] = lower_bound(b, b + n, sum[i]) - b + 2;
        low[i] = lower_bound(b, b + n, low[i]) - b + 2 - 1;
        high[i] = upper_bound(b, b + n, high[i]) - b + 2 - 1;
    }
    ll ans = 0;
    add(sum[0]);
    for (int i = 1; i <= n; i++)
    {
        ans += query(high[i]) - query(low[i]);
        add(sum[i]);
    }
    cout << ans;
    return 0;
}
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
int main()
{
    ll t, k, n;
    cin >> t;
    ll pre, now;
    while (t--)
    {
        pre = 2, now = 0;
        cin >> n >> k;
        for (ll i = 1; i <= n; i++)
        {
            if (pre > k)
            {
                pre -= k;
                now += k;
            }
            else
            {
                now += pre;
                pre = 0;
            }
            pre += now / 2;
        }
        cout << pre + now << endl;
    }
    return 0;
}
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

struct Edges
{
    int x, y, w;
    bool operator<(const Edges &a) const
    {
        return w < a.w;
    }
} edges[MS];
int n;
int root[MS], cnt[MS];
int find(int x)
{
    if (root[x] == x)
        return x;
    else
        return root[x] = find(root[x]);
}
int main()
{
    //ios::sync_with_stdio(false);
    //cin.tie(nullptr);
    int t;
    cin >> t;
    while (t--)
    {
        int a, b;
        ll ans = 0;
        cin >> n;
        for (int i = 0; i <= n; i++)
        {
            root[i] = i;
            cnt[i] = 1;
        }
        for (int i = 0; i < n - 1; i++)
        {
            cin >> edges[i].x >> edges[i].y >> edges[i].w;
        }
        sort(edges, edges + n - 1);
        for (int i = 0; i < n - 1; i++)
        {
            a = find(edges[i].x);
            b = find(edges[i].y);
            ans += 1LL * cnt[a] * cnt[b] * (edges[i].w + 1) - 1;
            root[b] = a;
            cnt[a] += cnt[b];
        }
        cout << ans << endl;
    }
    return 0;
}
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
struct node
{
    int cost;
    int t;

} fish[MS];
bool cmp(node &a, node &b)
{
    return 1.0 * a.cost / a.t > (1.0 * b.cost / b.t);
}
int main()
{
    //ios::sync_with_stdio(false);
    //cin.tie(nullptr);
    int n;
    scanf("%d", &n);
    ll cost = 0;
    ll ans = 0;
    for (int i = 1; i <= n; i++)
    {
        scanf("%d%d", &fish[i].t, &fish[i].cost);
        cost += fish[i].cost;
    }
    sort(fish + 1, fish + n + 1, cmp);
    for (int i = 1; i <= n; i++)
    {
        cost -= fish[i].cost;
        ans += cost * fish[i].t;
    }
    printf("%lld", ans);
    return 0;
}
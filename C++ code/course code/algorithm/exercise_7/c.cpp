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
    double x, y;
    bool operator<(const node &p) const { return x < p.x; }
} nodes[MS];
int n, m;
inline double dis(double h, double r) { return sqrt(r * r - h * h); }
int check(double r)
{
    int ans = 1;
    int i, j;
    double left = nodes[1].x - dis(nodes[1].y, r), right = nodes[1].x + dis(nodes[1].y, r);
    for (i = 2; i <= n; i++)
    {
        double dist = dis(nodes[i].y, r);
        double tl = nodes[i].x - dist, tr = nodes[i].x + dist;
        if (tl < right && tr > left)
        {
            left = max(tl, left), right = min(right, tr);
        }
        else
        {
            ++ans;
            left = tl, right = tr;
        }
    }
    return ans;
}
int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++)
    {
        scanf("%lf%lf", &nodes[i].x, &nodes[i].y);
    }
    sort(nodes + 1, nodes + n + 1);
    double l = 0, r = 2147483647, mid;
    while (r - l > 0.0001)
    {
        mid = (l + r) / 2;
        if (check(mid) > m)
            l = mid;
        else
            r = mid;
    }
    printf("%.3lf", l);
    return 0;
}
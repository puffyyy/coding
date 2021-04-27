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
inline double dis(double h, double r) { return sqrt(r * r - h * h); }
int n;
double r;
int main()
{
    cin >> n;
    cin >> r;
    int flag = 1;
    for (int i = 1; i <= n; i++)
    {
        cin >> nodes[i].x >> nodes[i].y;
        if (nodes[i].y > r)
            flag = 0;
    }
    if (!flag)
    {
        cout << "Mission Impossible" << endl;
        return 0;
    }
    sort(nodes + 1, nodes + n + 1);
    int ans = 0;
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
    ++ans;
    cout << ans;
    return 0;
}
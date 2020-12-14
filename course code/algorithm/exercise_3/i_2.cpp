#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <cstdlib>
#include <algorithm>
using namespace std;
typedef long long int ll;
const int maxm = 1e5 + 5;
double treesum[maxm];
int treecnt[maxm];
double dis[maxm];
int n;
double maxdis = -21;
struct Star
{
    double val, dis;
    int pos;
    bool operator<(const Star &o) const
    {
        return (val == o.val) ? (pos < o.pos) : (val < o.val);
    }
};
bool cmpdis(const Star &a, const Star &b)
{
    return a.dis < b.dis;
}
int lowbit(int x)
{
    return x & (-x);
}
void updatesum(int i, double k)
{
    while (i <= n)
    {
        treesum[i] += k;
        i += lowbit(i);
    }
}
void updatecnt(int i, int k)
{
    while (i <= n)
    {
        treecnt[i] += k;
        i += lowbit(i);
    }
}
double getsum(int i)
{
    //求A[1 - i]的和
    double res = 0;
    while (i > 0)
    {
        res += treesum[i];
        i -= lowbit(i);
    }
    return res;
}
int getcnt(int i)
{
    //求A[1 - i]的个数
    int res = 0;
    while (i > 0)
    {
        res += treecnt[i];
        i -= lowbit(i);
    }
    return res;
}
int main()
{
    scanf("%d", &n);
    Star *stars = new Star[n + 1];
    for (int i = 1; i <= n; ++i)
    {
        scanf("%lf%lf", &stars[i].val, &stars[i].dis);
        dis[i] = stars[i].dis;
    }
    sort(dis + 1, dis + 1 + n);
    for (int i = 1; i <= n; ++i)
        stars[i].pos = lower_bound(dis + 1, dis + 1 + n, stars[i].dis) - dis; //去重

    sort(stars + 1, stars + 1 + n);
    double ans = 0;
    double sum_to_i = 0;
    // sum_to_i = stars[1].dis;
    //
    for (int i = 1; i <= n; ++i)
    {
        int lcnt = getcnt(stars[i].pos);               // 或(stars[i].pos - 1) 下同
        double lsum = getsum(stars[i].pos);            // 在i左侧的离原点坐标和
        double lsum_to_i = lcnt * stars[i].dis - lsum; // 在i左侧的离当前点i 的距离和
        double rsum_to_i = sum_to_i - lsum - (i - 1 - lcnt) * stars[i].dis;
        ans += (lsum_to_i + rsum_to_i) * stars[i].val; // 当前的i是val最大的

        updatecnt(stars[i].pos, 1);
        updatesum(stars[i].pos, stars[i].dis);
        sum_to_i += stars[i].dis;
    }
    printf("%.3lf", ans);
    return 0;
}

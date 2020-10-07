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
typedef long long int ll;
const int maxm = 1e5 + 5;
double treesum[maxm];
int treecnt[maxm];
int n;
struct Star
{
    double val, dis;
    int v;
};
bool cmpdis(const Star &a, const Star &b)
{
    return a.dis < b.dis;
}
bool cmpval(const Star &a, const Star &b)
{
    return a.val < b.val;
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
    ios::sync_with_stdio(false);

    cin >> n;
    Star *stars = new Star[n + 1];
    for (int i = 1; i <= n; ++i)
    {
        cin >> stars[i].val >> stars[i].dis;
    }
    sort(stars + 1, stars + 1 + n, cmpval);
    for (int i = 1; i <= n; ++i)
        stars[i].v = i;
    sort(stars + 1, stars + 1 + n, cmpdis);

    double ans = 0;
    int cnt;
    double sum;
    //寻找比 i 小(距离比i小的中)的 val 计算
    for (int i = 1; i <= n; ++i) //正序 i前面的
    {
        cnt = getcnt(stars[i].v);
        sum = getsum(stars[i].v);
        ans += stars[i].val * (cnt * stars[i].dis - sum);
        updatecnt(stars[i].v, 1);
        updatesum(stars[i].v, stars[i].dis);
    }

    memset(treecnt, 0, sizeof(int) * maxm);
    memset(treesum, 0, sizeof(double) * maxm);

    for (int i = n; i >= 1; --i) //逆序 i后面的
    {
        cnt = getcnt(stars[i].v);
        sum = getsum(stars[i].v);
        ans += stars[i].val * (sum - cnt * stars[i].dis);
        updatecnt(stars[i].v, 1);
        updatesum(stars[i].v, stars[i].dis);
    }

    printf("%.3lf\n", ans);
    return 0;
}
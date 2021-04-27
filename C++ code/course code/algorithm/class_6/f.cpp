#include <cstdio>
#include <cmath>
#include <algorithm>
#include <cstring>
#include <iostream>
#define maxn 200010
#define INF 1145141919810114514LL
using namespace std;
struct Point
{
    double x, y;
    Point(double xx = 0, double yy = 0) { x = xx, y = yy; }
    Point operator-(const Point &o) const
    {
        return Point(x - o.x, y - o.y);
    }
    double operator^(const Point &o) const
    {
        return x * o.y - y * o.x;
    }
    double dis2(Point o)
    {
        return fabs(x - o.x) + fabs(y - o.y);
    }
} p[maxn], s[maxn];
int tmp[maxn];
int n;

inline bool cmp2(Point a, Point b)
{
    if (a.x == b.x)
        return a.y < b.y;
    else
        return a.x < b.x;
}
inline bool cmpIndex(int a, int b)
{
    return p[a].y < p[b].y;
}
double merge(int lo, int hi)
{
    double dis = INF;
    if (lo == hi)
        return dis;
    if (lo + 1 == hi)
        return p[lo].dis2(p[hi]);
    int mi = (lo + hi) >> 1;
    double dis1 = merge(lo, mi);
    double dis2 = merge(mi + 1, hi);
    if (dis1 < dis)
        dis = dis1;
    if (dis2 < dis)
        dis = dis2;
    int ccnt = 0;
    for (int i = lo; i <= hi; ++i)
    {
        double Abs = p[i].x - p[mi].x;
        if (Abs < 0)
            Abs = -Abs;
        if (Abs <= dis)
            tmp[ccnt++] = i;
    }
    sort(tmp, tmp + ccnt, cmpIndex);
    for (int i = 0; i < ccnt; ++i)
    {
        for (int j = i + 1; j < ccnt && p[tmp[j]].y - p[tmp[i]].y < dis; ++j)
        {
            double dis3 = p[tmp[i]].dis2(p[tmp[j]]);
            if (dis > dis3)
                dis = dis3;
        }
    }
    return dis;
}
double get_nearset()
{
    sort(p + 1, p + n + 1, cmp2);
    return merge(1, n);
}
int main()
{
    while (scanf("%d", &n) != EOF)
    {
        for (int i = 1; i <= n; ++i)
            scanf("%lf%lf", &p[i].x, &p[i].y);
        printf("%.3lf", get_nearset());
    }
}
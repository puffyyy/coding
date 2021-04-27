#include <cstdio>
#include <cmath>
#include <algorithm>
#define sqr(x) (x) * (x)
#define maxn 1005
using namespace std;
struct Point
{
    double x, y;
    Point() {}
    Point(double x, double y) : x(x), y(y) {}
    bool operator<(const Point &p) const { return x < p.x; }
} q[maxn];
struct circle
{
    double x, y, r;
    bool operator<(const circle &p) const { return r > p.r; }
    double dis(const circle &p) const { return sqrt(sqr(x - p.x) + sqr(y - p.y)); }
} a[maxn];
const double eps = 1e-8, inf = 1e20, Pi = acos(-1);
int n;
double f(double x)
{
    int top = 0;
    double l = -inf, r = -inf, ret = 0;
    for (int i = 1; i <= n; i++)
        if (fabs(x - a[i].x) < a[i].r)
        {
            double len = sqrt(sqr(a[i].r) - sqr(x - a[i].x));
            q[++top] = Point(a[i].y - len, a[i].y + len);
        }
    sort(q + 1, q + 1 + top);
    for (int i = 1; i <= top; i++)
        if (q[i].x > r)
            ret += r - l, l = q[i].x, r = q[i].y;
        else
            r = max(r, q[i].y);
    return ret += r - l;
}
//∫(r-l) f(x)dx=(r−l)*(f(l)+4f(mid)+f(r))/6
double Simpson(double L, double M, double R, double fL, double fM, double fR, int dep) //区间起点中点终点 函数在三点上的值 迭代次数
{
    double M1 = (L + M) / 2, M2 = (M + R) / 2, fM1 = f(M1), fM2 = f(M2);
    double g1 = (M - L) * (fL + 4 * fM1 + fM) / 6, g2 = (R - M) * (fM + 4 * fM2 + fR) / 6, g = (R - L) * (fL + 4 * fM + fR) / 6;
    if (dep > 11 && fabs(g - g1 - g2) < eps)
        return g;
    return Simpson(L, M1, M, fL, fM1, fM, dep + 1) + Simpson(M, M2, R, fM, fM2, fR, dep + 1);
}
void unique_cir()
{
    int cnt = 0, flag = 1;
    sort(a + 1, a + 1 + n);
    for (int i = 1; i <= n; i++)
    {
        flag = 1;
        for (int j = 1; j <= cnt; j++)
            if (a[i].r + a[i].dis(a[j]) <= a[j].r) //包含
            {
                flag = 0;
                break;
            }
        if (flag)
            a[++cnt] = a[i];
    }
    n = cnt;
}
int main()
{
    double l = inf, r = -inf;
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
    {
        scanf("%lf%lf%lf", &a[i].x, &a[i].y, &a[i].r);
        l = min(l, a[i].x - a[i].r);
        r = max(r, a[i].x + a[i].r);
    }
    unique_cir();
    printf("%.3f", Simpson(l, (l + r) / 2, r, f(l), f((l + r) / 2), f(r), 0));
    return 0;
}
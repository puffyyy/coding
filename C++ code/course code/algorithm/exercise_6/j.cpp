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
#include <iomanip>
#define sqr(x) ((x) * (x))
#define eps 1e-7
using namespace std;
const int MS = 1e6 + 5;
int n;
struct Point
{
    double x, y;
    Point() {}
    Point(double x, double y) : x(x), y(y) {}
    double dis(Point &a) { return sqrt(sqr(a.x - x) + sqr(a.y - y)); }
} P[MS];
Point get_cir(Point &p1, Point &p2, Point &p3)
{
    Point res;
    double a = p2.x - p1.x, b = p2.y - p1.y, c = p3.x - p2.x, d = p3.y - p2.y;
    double e = sqr(p2.x) + sqr(p2.y) - sqr(p1.x) - sqr(p1.y);
    double f = sqr(p3.x) + sqr(p3.y) - sqr(p2.x) - sqr(p2.y);
    res.x = (f * b - e * d) / (c * b - a * d) / 2.0;
    res.y = (a * f - e * c) / (a * d - b * c) / 2.0;
    return res;
}
double find_cir(Point &o)
{
    double R = 0;
    for (int i = 1; i < n; i++)
    {
        if (o.dis(P[i]) - R > eps)
        {
            o = P[i], R = 0;
            for (int j = 1; j < i; j++)
            {
                if (o.dis(P[j]) - R > eps)
                {
                    o.x = (P[i].x + P[j].x) / 2, o.y = (P[i].y + P[j].y) / 2;
                    R = P[i].dis(P[j]) / 2;
                    for (int k = 1; k < j; k++)
                    {
                        if (o.dis(P[k]) - R > eps)
                        {
                            o = get_cir(P[i], P[j], P[k]);
                            R = o.dis(P[i]);
                        }
                    }
                }
            }
        }
    }
    return R;
}
int main()
{
    //ios::sync_with_stdio(false);
    //cin.tie(nullptr);
    cin >> n;
    for (int i = 1; i <= n; i++)
        cin >> P[i].x >> P[i].y;
    random_shuffle(P + 1, P + n + 1);
    Point c = P[1];
    double r = find_cir(c);

    cout << setiosflags(ios::fixed);
    cout << setprecision(4) << c.x << " " << setprecision(4) << c.y << " " << setprecision(4) << r;
    return 0;
}
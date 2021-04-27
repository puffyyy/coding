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
const double esp_d = 1e-15;
const int MS = 1e5 + 5;
struct Point
{
    double x, y;
    Point(double xx, double yy) : x(xx), y(yy) {}
    void operator=(const Point &b)
    {
        x = b.x, y = b.y;
    }
};
struct Segment
{
    Point a, b;
    Segment(Point aa, Point bb) : a(aa), b(bb) {}
};

struct Vec
{
    double x, y;
    Vec(Point a, Point b)
    {
        x = b.x - a.x, y = b.y - a.y;
    }
};
inline double cross_product(double x1, double y1, double x2, double y2)
{
    return x1 * y2 - x2 * y1;
}
inline double cross_product(const Vec &a, const Vec &b) //a 在 b 的顺时针
{
    return a.x * b.y - a.y * b.x;
}
double clockwise(double x1, double y1, double x2, double y2) //x1,y1 在 x2,y2的顺时针方向则返回 1
{
    double x = cross_product(x1, y1, x2, y2);
    if (x < esp_d || x > -esp_d) //共线
        return 0;
    return x > 0 ? 1 : -1;
}
inline double clockwise(const Vec &a, const Vec &b)
{
    double x = cross_product(a, b);
    if (x < esp_d || x > -esp_d) //共线
        return 0;
    return x > 0 ? 1 : -1;
}
inline bool on_segment(Point a, Point b, Point c)
{
    return min(a.x, b.x) <= c.x && c.x <= max(a.x, b.x) && min(a.y, b.y) <= c.y && c.y <= max(a.y, b.y);
}
bool segment_intersect(Point p1, Point p2, Point p3, Point p4)
{
    double d1, d2, d3, d4;
    d1 = cross_product(Vec(p3, p4), Vec(p3, p1));
    d2 = cross_product(Vec(p3, p4), Vec(p3, p2));
    d3 = cross_product(Vec(p1, p2), Vec(p1, p3));
    d4 = cross_product(Vec(p1, p2), Vec(p1, p4));
    if (((d1 > 0 && d2 < 0) || (d1 < 0 && d2 > 0)) && ((d3 > 0 && d4 < 0) || (d3 < 0 && d4 > 0)))
        return true;
    else if (d1 == 0 && on_segment(p3, p4, p1))
        return true;
    else if (d2 == 0 && on_segment(p3, p4, p2))
        return true;
    else if (d3 == 0 && on_segment(p1, p2, p3))
        return true;
    else if (d4 == 0 && on_segment(p1, p2, p4))
        return true;
    return false;
}
int main()
{
    int n;
    while (cin >> n)
    {
        int x, y, x2, y2;
        int flag = 1;
        vector<Segment> li;
        li.push_back(Segment(Point(0, 0), Point(0, 0)));
        for (int i = 1; i <= n; i++)
        {
            cin >> x >> y >> x2 >> y2;
            li.push_back(Segment(Point(x, y), Point(x2, y2)));
        }
        for (int i = 1; i <= n; i++)
        {
            flag = 1;
            for (int j = i + 1; j <= n; j++)
            {
                if (segment_intersect(li[i].a, li[i].b, li[j].a, li[j].b))
                {
                    flag = 0;
                    break;
                }
            }
            if (flag)
                printf("%d ", i);
        }
        putchar('\n');
    }

    return 0;
}
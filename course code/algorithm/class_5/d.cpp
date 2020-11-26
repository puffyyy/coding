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
inline int clockwise(const Vec &a, const Vec &b)
{
    double x = cross_product(a, b);
    if (x < esp_d && x > -esp_d) //共线
    {
        if (a.x * b.x + a.y * b.y > 0)
            return 1;
        else
            return 2;
    }
    return x > 0 ? 3 : 4;
}

int main()
{
    int n;
    scanf("%d", &n);
    vector<Point> PO;
    double x, y;
    for (int i = 0; i < n; i++)
    {
        scanf("%lf%lf", &x, &y);
        PO.push_back(Point(x, y));
    }
    Vec now(PO[0], PO[1]);
    Vec next = Vec(Point(0, 0), Point(0, 0));
    for (int i = 1; i < n - 1; i++)
    {
        next = Vec(PO[i], PO[i + 1]);
        switch (clockwise(now, next))
        {
        case 1:
            printf("forward\n");
            break;
        case 2:
            printf("back\n");
            break;
        case 3:
            printf("left\n");
            break;
        case 4:
            printf("right\n");
            break;
        }
        now = next;
    }
    return 0;
}
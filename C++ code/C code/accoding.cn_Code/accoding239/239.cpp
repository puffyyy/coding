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
struct Point
{
    double x, y;
    Point(double xx = 0, double yy = 0) : x(xx), y(yy) {}
    bool operator<(const Point &b) const
    {
        return y == b.y ? x < b.x : y < b.y;
    }
    void operator=(const Point &b)
    {
        x = b.x, y = b.y;
    }
};
struct Vec
{
    double x, y;
    Vec(Point a, Point b)
    {
        x = b.x - a.x, y = b.y - a.y;
    }
    Vec(double xx, double yy) : x(xx), y(yy) {}
    double dis()
    {
        return x * x + y * y;
    }
};
inline double cross_product(const Vec &a, const Vec &b)
{
    return a.x * b.y - a.y * b.x;
}
inline bool clockwise(const Vec &a, const Vec &b)
{
    double x = cross_product(a, b);
    return x > 0 ? true : false;
}
Point get_point(const Point *a = NULL)
{
    static Point start;
    if (a)
        start = *a;
    return start;
}
Point ssss;
bool cmp_point_angle(const Point &a, const Point &b)
{
    static Point start = get_point();
    return cross_product(Vec(start, a), Vec(start, b)) > 0 ? 1 : 0;
}
vector<Point> S;         //凸包集合
vector<Point> point_set; //点集合
void garham_scan(vector<Point> &Q)
{
    vector<Point>::iterator left = Q.begin();
    for (vector<Point>::iterator it = Q.begin(); it != Q.end(); it++)
    {
        if (*it < *left)
            left = it;
    }
    swap(*Q.begin(), *(left));

    sort(Q.begin() + 1, Q.end(), cmp_point_angle);
    Point start = Q.front();
    get_point(&start);
    left = Q.begin();
    S.push_back(*(left++));
    if (Q.size() < 2)
        return;
    S.push_back(*(left++));

    for (; left != Q.end(); left++)
    {
        vector<Point>::iterator top_p = S.end() - 1;
        while (S.size() > 1 && !clockwise(Vec(*(top_p - 1), *top_p), Vec(*top_p, *left)))
        {
            S.pop_back();
            top_p = S.end() - 1;
        }
        S.push_back(*left);
    }
}
int main()
{
    int n;
    scanf("%d", &n);

    double x, y;
    double ans = -1;
    for (double i = 0; i < n; i++)
    {
        scanf("%lf%lf", &x, &y);
        point_set.push_back(Point(x, y));
    }
    garham_scan(point_set);
    for (vector<Point>::iterator it = S.begin(); it != S.end(); it++)
        for (vector<Point>::iterator jt = S.begin(); jt != S.end(); jt++)
        {
            ans = max(ans, Vec(*it, *jt).dis());
        }
    if (S.size() == 1)
    {
        ans = 0;
        printf("%.6lf\n", ans);
    }
    else
        printf("%.6lf\n", sqrt(ans));

    return 0;
}
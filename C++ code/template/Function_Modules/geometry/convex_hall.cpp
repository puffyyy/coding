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
    Point(double xx = 0, double yy = 0) : x(xx), y(yy) {}
    bool operator<(const Point &b) const
    {
        return y == b.y ? x < b.x : y < b.y;
    }
    bool operator!=(const Point &b) const
    {
        return y == b.y && x == b.x;
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
};
inline double cross_product(const Vec &a, const Vec &b)
{
    return a.x * b.y - a.y * b.x;
}
inline bool clockwise(const Vec &a, const Vec &b)
{
    double x = cross_product(a, b);
    if (x < esp_d && x > -esp_d) //共线
        return 0;
    return x > 0 ? true : false;
}
inline double phi(const Vec &a, const Vec &b)
{
    if (a.x > 0 && b.y < 0)
        return -0x7fffffff;
    if (a.x < 0 && b.y > 0)
        return -0x7fffffff;
    double x = a.x * b.x + a.y * b.y;
    if (x < esp_d && x > -esp_d) //垂直
        // return a.x * b.x > 0 ? 0 : 0x7fffffff;
        return 0;
    return x / sqrt(b.x * b.x + b.y * b.y);
}
Point get_point(const Point *a = NULL)
{
    static Point start; //只会初始化一次 当多组数据时要改成全局变量 89行
    if (a)
        start = *a;
    return start;
}
bool cmp_point_angle(const Point &a, const Point &b)
{
    static Point start = get_point();
    return cross_product(Vec(start, a), Vec(start, b)) > 0 ? 1 : 0;
}
vector<Point> Q;
vector<Point> S;         //凸包集合
vector<Point> point_set; //点集合
void garham_scan()
{
    Q = point_set; //deep copy
    vector<Point>::iterator left = Q.begin();
    for (vector<Point>::iterator it = Q.begin(); it != Q.end(); it++)
    {
        if (*it < *left)
            left = it;
    }
    Point start = *left;
    get_point(&start);
    Q.erase(left);
    sort(Q.begin(), Q.end(), cmp_point_angle);
    if (Q.size() < 2)
        return;

    left = Q.begin();
    S.push_back(start);
    S.push_back(*(left++));
    S.push_back(*(left++));
    for (; left != Q.end(); left++)
    {
        vector<Point>::iterator top_p = S.end() - 1;
        int tmp = clockwise(Vec(*(top_p - 1), *top_p), Vec(*top_p, *left));
        while (!clockwise(Vec(*(top_p - 1), *top_p), Vec(*top_p, *left)))
        {
            S.pop_back();
            top_p = S.end() - 1;
        }
        S.push_back(*left);
    }
}
void jarvis()
{
    Q = point_set; //deep copy
    vector<Point>::iterator start = Q.begin(), end = Q.begin(), next, min_p;
    vector<bool> visit(Q.size(), 0);
    for (vector<Point>::iterator it = Q.begin(); it != Q.end(); it++)
    {
        if (*it < *start)
            start = it;
        if (it->y > end->y)
            end = it;
    }
    S.push_back(*start);
    *(visit.begin() + (start - Q.begin())) = 1;
    next = start;
    do
    {
        double min_phi = -0x7fffffff;
        for (vector<Point>::iterator it = Q.begin(); it != Q.end(); it++)
        {
            double x = phi(Vec(1, 0), Vec(*next, *it));
            if (it != next && min_phi < x)
            {
                min_p = it;
                min_phi = x;
            }
            else if (it != next && (x < esp_d && x > -esp_d) && min_p->x - next->x < it->x - next->x)
            {
                min_p = it;
                min_phi = x;
            }
        }
        S.push_back(*min_p);
        next = min_p;
    } while (next != end);
    next = end;
    do
    {
        double min_phi = -0x7fffffff;
        for (vector<Point>::iterator it = Q.begin(); it != Q.end(); it++)
        {
            double x = phi(Vec(-1, 0), Vec(*next, *it));
            if (it != next && min_phi < x)
            {
                min_p = it;
                min_phi = x;
            }
            else if (it != next && (x < esp_d + min_phi && x > min_phi - esp_d) && min_p->x - next->x < it->x - next->x)
            {
                min_p = it;
                min_phi = x;
            }
        }
        S.push_back(*min_p);
        next = min_p;
    } while (next != start);
    S.pop_back();
}
int main()
{

    int n = 5;
    cin >> n;
    double x, y;
    for (int i = 0; i < n; i++)
    {
        cin >> x >> y;
        point_set.push_back(Point(x, y));
    }
    garham_scan();
    for (vector<Point>::iterator it = S.begin(); it != S.end(); it++)
        cout << "point"
             << "x:" << it->x << " y:" << it->y << endl;
    return 0;
}
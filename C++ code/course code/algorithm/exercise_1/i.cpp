#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <cstdlib>
#include <algorithm>
#include <vector>
using namespace std;
double inf = 999000.0;
struct Point
{
    int x, y;
    int no;
    bool color; // true = black
    double deg;
    int match;
    Point(int _x = 0, int _y = 0, int _no = 0, bool _color = true, double _deg = 0.0, int _match = -1) : x(_x), y(_y), no(_no), color(_color), deg(_deg), match(_match){};
    // bool operator<(const Point &a) const
    // { //重载<操作符。可以对两个node使用<操作符进行比较
    //     if (x == a.x)
    //         return y < a.y;
    //     return x < a.x;
    // }
};

vector<Point> ans;
bool cmp(const Point &a, const Point &b)
{
    if (a.x == b.x)
        return a.y < b.y;
    return a.x < b.x;
}
bool cmpdeg(const Point &a, const Point &b)
{
    return a.deg < b.deg;
}
bool cmpans(const Point &a, const Point &b)
{
    return a.no < b.no;
}
void caldeg(int choose, vector<Point> &points, int left, int right)
{
    for (int i = left; i <= right; i++)
    {
        if (points[i].match == -1 && i != choose)
            if (points[i].x - points[choose].x == 0)
                points[i].deg = inf;
            else
                points[i].deg = 1.0 * double(points[i].y - points[choose].y) / double(points[i].x - points[choose].x);
    }
}
int findmin(vector<Point> &points, int left, int right)
{
    int pos = left;
    for (int i = left + 1; i <= right; i++)
    {
        if (cmp(points[i], points[pos]))
            pos = i;
    }
    return pos;
}
int cmp1(const void *a, const void *b)
{
    return (*(Point *)a).deg < (*(Point *)b).deg ? -1 : 1;
}
void solve(vector<Point> &points, int left, int right)
{
    if (left >= right)
        return;
    if (left + 1 == right)
    {
        points[left].match = points[right].no;
        points[right].match = points[left].no;
        return;
    }
    int choose = findmin(points, left, right);

    swap(points[choose], points[left]);
    choose = left;
    caldeg(choose, points, left, right);
    //sort(points.begin() + left, points.begin() + right, cmpdeg);

    qsort(&points[left + 1], right - left, sizeof(points[0]), cmp1);
    int cnt = 0;
    if (points[choose].color == true)
        cnt = 1;
    else
        cnt = -1;
    for (int i = left; i <= right; i++)
    {
        if (i == choose)
            continue;
        if (points[i].match != -1)
            continue;
        if (points[i].color == true)
            ++cnt;
        else
            --cnt;
        if (cnt == 0)
        {
            points[choose].match = points[i].no;
            points[i].match = points[choose].no;
            solve(points, left + 1, i - 1);
            solve(points, i + 1, right);
        }
    }
}
int main()
{
    int n;
    cin >> n;
    vector<Point> points;
    for (int i = 0; i < n; ++i)
    {
        int x, y, no;
        cin >> x >> y >> no;
        Point tmp(x, y, no, true);
        points.push_back(tmp);
    }
    for (int i = 0; i < n; ++i)
    {
        int x, y, no;
        cin >> x >> y >> no;
        Point tmp(x, y, no, false);
        points.push_back(tmp);
    }
    solve(points, 0, points.size() - 1);
    for (int i = 0; i < points.size(); ++i)
    {
        if (points[i].color == true)
            ans.push_back(points[i]);
    }
    sort(ans.begin(), ans.end(), cmpans);
    for (int i = 0; i < ans.size(); ++i)
    {
        cout << ans[i].match << " ";
    }
    return 0;
}
/*
3
-1 2 0
0 1 1 
1 0 2
0 0 0
-1 -1 1
2 2 2
*/

/*
4
1 0 0 
2 0 1
2 2 2
0 1 3
0 -1 0 
3 1 1 
4 3 2
-2 3 3
*/
/*
4
-2 2 0
-1 0 1
1 0 2 
2 3 3
-1 1 0
2 -3 1
3 1 2
5 -1 3
*/
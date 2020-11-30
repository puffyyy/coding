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

int main()
{
    long double x, y, r;
    long double ax, ay, bx, by;
    while (cin >> x >> y >> r)
    {
        cin >> ax >> ay >> bx >> by;
        long double c, a, b; //line : ax+by+c=0
        c = (ax - bx) * ay - (ay - by) * ax;
        a = ay - by, b = bx - ax;
        long double ret = 0;
        long double dis_line_to_cir = fabs(a * x + b * y + c) / (sqrt(a * a + b * b));
        long double dis_s2t = hypot(ax - bx, ay - by);
        if (dis_line_to_cir < r)
        {
            long double d1 = sqrt((x - ax) * (x - ax) + (y - ay) * (y - ay) - r * r);
            long double d2 = sqrt((x - bx) * (x - bx) + (y - by) * (y - by) - r * r);
            long double phi = (acos(dis_line_to_cir / sqrt((x - ax) * (x - ax) + (y - ay) * (y - ay))) + acos(dis_line_to_cir / sqrt((x - bx) * (x - bx) + (y - by) * (y - by)))) - (acos((r) / d1) + acos((r) / d2));
            ret = d1 + d2 + r * phi;
        }
        else
        {
            ret = dis_s2t;
        }
        printf("%.10Lf", ret);
    }
    return 0;
}
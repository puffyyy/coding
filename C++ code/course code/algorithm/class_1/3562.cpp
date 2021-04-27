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
struct point
{
    ll x, y;
    /*
    * * * * * * y
    *
    *
    *
    x
    */
    point(ll xx = 0, ll yy = 0) : x(xx), y(yy) {}

    point rotateL90()
    {
        return point(y, x); //对应第一部分的交换横纵坐标
    }
    point rotateR90(ll len)
    {
        point tmp = rotateL90();
        return point(len + 1 - tmp.x, len + 1 - tmp.y);
    }
    point operator+(const point &o) const //重载运算符
    {
        return point(x + o.x, y + o.y);
    }
    ll dis(const point &o) const
    {
        return (x - o.x) * (x - o.x) + (y - o.y) * (y - o.y);
    }
};

point find(ll n, ll num)
{
    ll sub_length = 1 << (n - 1);            //一半边长
    ll sub_square = sub_length * sub_length; //1/4个正方形
    if (n == 1)                              //递归终点
    {
        if (num == 1)
            return point(1, 1);
        if (num == 2)
            return point(2, 1);
        if (num == 3)
            return point(2, 2);
        if (num == 4)
            return point(1, 2);
    }
    point ret;
    if (num <= sub_square)
    {
        ret = find(n - 1, num);
        return ret.rotateL90();
    }
    else if (num <= 2 * sub_square)
    {
        ret = find(n - 1, num - sub_square); //相当于前一个图形的第 num - sub_square个方块
        return ret + point(sub_length, 0);
    }
    else if (num <= 3 * sub_square)
    {
        ret = find(n - 1, num - 2 * sub_square); //同上
        return ret + point(sub_length, sub_length);
    }
    else
    {
        ret = find(n - 1, num - 3 * sub_square);
        return ret.rotateR90(sub_length) + point(0, sub_length);
    }
}
int main()
{
    ll a, b;
    int n;
    while (~scanf("%d%lld%lld", &n, &a, &b))
    {
        printf("%lld\n", find(n, a).dis(find(n, b)));
    }
    return 0;
}
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

struct Point
{
    long long x, y;
};
typedef struct Point point;
void left(point *a)
{
    long long tmp;
    tmp = a->x;
    a->x = a->y;
    a->y = tmp;
    return;
}
void right(point *a, long long len)
{
    left(a);
    a->x = len + 1 - a->x;
    a->y = len + 1 - a->y;
    return;
}
point find(long long n, long long num)
{
    if (n == 1)
    {
        point tmp;
        switch (num)
        {
        case 1:
            tmp.x = 1, tmp.y = 1;
            break;
        case 2:
            tmp.x = 1, tmp.y = 2;
            break;
        case 3:
            tmp.x = 2, tmp.y = 2;
            break;
        case 4:
            tmp.x = 2, tmp.y = 1;
            break;
        }
        return tmp;
    }
    long long sub_len = 1 << (n - 1);
    long long one_quarter = sub_len * sub_len;
    point ret;
    if (num <= one_quarter)
    {
        ret = find(n - 1, num);
        left(&ret);
        return ret;
    }
    else if (num <= 2 * one_quarter)
    {
        ret = find(n - 1, num - one_quarter);
        ret.y += sub_len;
        return ret;
    }
    else if (num <= 3 * one_quarter)
    {
        ret = find(n - 1, num - 2 * one_quarter);
        ret.x += sub_len, ret.y += sub_len;
        return ret;
    }
    else
    {
        ret = find(n - 1, num - 3 * one_quarter);
        right(&ret, sub_len);
        ret.x += sub_len;
        return ret;
    }
}
long long dis(point a, point b)
{
    return (b.x - a.x) * (b.x - a.x) + (b.y - a.y) * (b.y - a.y);
}
int main()
{
    long long n, a, b;
    while (~scanf("%d%lld%lld", &n, &a, &b))
    {
        point pa = find(n, a);
        point pb = find(n, b);
        printf("%lld\n", dis(pa, pb));
    }
    return 0;
}
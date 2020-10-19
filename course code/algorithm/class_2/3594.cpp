#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#define MS 100005
int a[MS];
int b[MS];
int *c_upperbound(int *begin, int *end, int target)
{
    if (end - begin == 0)
        return end;
    int *left, *mid, *right;
    left = begin, right = end;
    while (left < right) //终止条件是 left == right 左闭右开
    {
        mid = left + (right - left) / 2;
        if (*mid == target)
        {
            left = mid + 1; // 注意
        }
        else if (*mid < target)
        {
            left = mid + 1;
        }
        else if (*mid > target)
        {
            right = mid;
        }
    }
    return left; // 或 right
}
int main()
{
    int n;

    while (~scanf("%d", &n))
    {
        for (int i = 0; i < n; ++i)
        {
            scanf("%d", a + i);
        }
        int top = -1;
        int pos;
        for (int i = n - 1; i >= 0; --i)
        {
            pos = c_upperbound(b, b + top + 1, a[i]) - b;
            if (pos > top)
                ++top;
            b[pos] = a[i];
        }
        printf("%d\n", top + 1);
    }
    return 0;
}
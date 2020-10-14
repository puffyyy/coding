#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
int a[100005];
int *c_lowerbound(int *begin, int *end, int target)
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
            right = mid;
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
    // *left 时第一个大于target的元素  *(left-1) 可能是target
}
int main()
{
    int n, q, tar;
    scanf("%d", &n);
    register int i;
    for (i = 0; i < n; ++i)
        scanf("%d", a + i);

    scanf("%d", &q);
    int *start = a;
    int *end = a + n;
    int pos;
    while (q--)
    {
        scanf("%d", &tar);
        pos = c_lowerbound(start, end, tar) - start;
        if (a[pos] == tar)
        {
            printf("Yes %d %d\n", pos + 1, (c_upperbound(start, end, tar) - start) - pos);
        }
        else
            printf("No\n");
    }
    return 0;
}
#include <stdio.h>
#include <string.h>
int a[100001];
int binarysearch_left(int lenth, int x)
{
    int left = 0, right = lenth - 1;
    while (left <= right)
    {
        int mid = left + ((right - left) >> 1);
        if (a[mid] >= x)
            right = mid - 1;
        else
            left = mid + 1;
    }
    if (a[left] == x)
        return left;
    else
        return -1;
}
int binarysearch_right(int lenth, int x)
{
    int left = 0, right = lenth - 1, mid;
    while (left <= right)
    {
        mid = left + ((right - left) >> 1);
        if (a[mid] <= x)
            left = mid + 1;
        else
            right = mid - 1;
    }
    if (a[right] == x)
        return right;
    else
        return -1;
}
int binarysearchleftcnt(int x, int len) //小于x的个数 要求升序 下标从0开始
{
    int mid, l, r;
    l = 0, r = len;
    while (l < r)
    {
        mid = (l + r) >> 1;
        if (a[mid] < x)
            l = mid + 1;
        else
            r = mid;
    }
    return l;
}
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
    int n, i, t;
    scanf("%d", &n);
    for (i = 0; i < n; i++)
        scanf("%d", &a[i]);
    scanf("%d", &t);
    for (; t > 0; t--)
    {
        scanf("%d", &i);
        if (binarysearch_left(n, i) != -1)
            printf("%d %d\n", binarysearch_left(n, i) + 1, binarysearch_right(n, i) + 1);
        else
            printf("-1\n");
    }

    return 0;
}
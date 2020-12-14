#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#define MS 100005
int a;
int dp[MS];
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
        else if (*mid > target)
        {
            left = mid + 1;
        }
        else if (*mid < target)
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
        int top = 0;
        for (int i = 1; i <= n; i++)
        {
            scanf("%d", &a);
            int pos = c_upperbound(dp, dp + top, a) - dp;
            dp[pos] = a;
            top = top + (pos == top ? 1 : 0);
        }
        printf("%d\n", top);
    }

    return 0;
}
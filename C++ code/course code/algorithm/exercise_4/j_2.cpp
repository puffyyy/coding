#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include <limits.h>
using namespace std;
typedef long long int ll;
const int MS = 1e6 + 5;
int a[MS], b[MS];
int n, m;
double findMedianSortedArrays(int *nums1, int *nums2)
{
    if (n > m)
    {
        swap(n, m);
        return findMedianSortedArrays(nums2, nums1);
    }
    int total_cnt_left = (m + n + 1) >> 1;
    int left = 0, right = n;
    int i, j;
    while (left < right)
    {
        i = (right + left + 1) >> 1;
        if (nums1[i - 1] > nums2[total_cnt_left - i])
            right = i - 1;
        else
            left = i;
    }
    i = left, j = total_cnt_left - i;
    int nums1LeftMax = i == 0 ? INT_MIN : nums1[i - 1];
    int nnums1RightMin = i == n ? INT_MAX : nums1[i];
    int nums2LeftMax = j == 0 ? INT_MIN : nums2[j - 1];
    int nums2RightMin = j == m ? INT_MAX : nums2[j];

    if ((n + m) & 1 == 1)
        return max(nums1LeftMax, nums2LeftMax);
    else
        return (max(nums1LeftMax, nums2LeftMax) + min(nnums1RightMin, nums2RightMin)) / 2.0;
}
int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 0; i < n; i++)
        scanf("%d", a + i);
    for (int i = 0; i < m; i++)
        scanf("%d", b + i);
    printf("%.2lf", findMedianSortedArrays(a, b));
    return 0;
}
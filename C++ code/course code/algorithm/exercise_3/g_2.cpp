#include <iostream>
#include <cstdio>
using namespace std;
int n, m;
bool check(int nums[], int x)
{
    long long sum = 0;
    int cnt = 1;
    for (int i = 0; i < n; i++)
    {
        if (sum + nums[i] > x)
        {
            cnt++;
            sum = nums[i];
        }
        else
            sum += nums[i];
    }
    return cnt <= m;
}

int binarySearch(int nums[])
{
    long long left = 0, right = 0;
    for (int i = 0; i < n; i++)
    {
        right += nums[i]; //sum of elements
        if (left < nums[i])
            left = nums[i]; //max element
    }
    while (left < right) //寻找左侧边界的二分搜索
    {
        long long mid = (left + right) >> 1;
        if (check(nums, mid))
            right = mid;
        else
            left = mid + 1;
    }
    return left;
}
int main()
{
    ios::sync_with_stdio(false);
    cin >> n >> m;
    int *a = new int[n + 1]();
    for (int i = 0; i < n; ++i)
        cin >> a[i];
    cout << binarySearch(a);
    return 0;
}
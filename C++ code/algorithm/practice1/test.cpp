#include <iostream>
#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include <stack>
#include <queue>
using namespace std;
const long long maxn = 1e3 + 5;
long long n;
long long a[maxn], sta[maxn];
/*
1 2 3 4 1
*/
int solve()
{
    long long top = 0;
    long long sum = 0, ans = 0;
    for (long long i = 1; i <= n; i++) // 求以a[i]位置为结尾的最大值和
    {                                  // 下降
        while (top > 0 && a[sta[top]] < a[i])
        {
            long long num = a[sta[top]];
            sum -= num * (sta[top] - sta[top - 1]);
            top--;
        }
        sta[++top] = i;
        sum += a[i] * (sta[top] - sta[top - 1]);
        ans += sum;
    }
    return ans;
}
int main()
{
    n = 5;
    for (int i = 1; i <= n; i++)
        cin >> a[i];
    solve();
    return 0;
}
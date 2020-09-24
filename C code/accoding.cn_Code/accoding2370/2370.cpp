#include <iostream>
#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include <stack>
#include <queue>
using namespace std;
const long long maxn = 50005;
long long n;
long long a[maxn], sta[maxn];
/*
1 2 3 4 1
*/
long long solvemax()
{
    long long top = 0;
    long long sum = 0, ans = 0;
    for (long long i = 1; i <= n; i++)        // 求以a[i]位置为结尾的最大值和
    {                                         // 从栈顶到栈底递增
        while (top > 0 && a[sta[top]] < a[i]) //栈非空  当前值大于栈顶
        {
            long long num = a[sta[top]];
            sum -= num * (sta[top] - sta[top - 1]); //更正到包含位置i序列的最大值 减去上一次的
            top--;
        }
        sta[++top] = i;
        sum += a[i] * (sta[top] - sta[top - 1]); //+包含位置 i 序列 的最大值
        // a[i] 是当前栈中最小的 乘以从哪开始 到当前位置i的长度  a[i]*(lenth)
        ans += sum; //a[i]位置为结尾的和
    }
    return ans;
}
long long solvemin()
{
    long long top = 0;
    long long sum = 0, ans = 0;
    for (long long i = 1; i <= n; i++)
    {
        while (top > 0 && a[sta[top]] > a[i])
        {
            sum -= a[sta[top]] * (sta[top] - sta[top - 1]);
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
    // n = 5;
    cin >> n;
    for (int i = 1; i <= n; i++)
        cin >> a[i];
    cout << solvemax() - solvemin();
    return 0;
}
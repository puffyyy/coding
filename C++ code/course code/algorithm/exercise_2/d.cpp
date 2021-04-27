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
ll a[51] = {1, 1};
ll fun1(int n) //到达 n 的最后一次只跳 1 2的
{
    if (n < 0)
        return 0;
    if (a[n] != 0)
        return a[n];
    a[n] = fun1(n - 1) + fun1(n - 2) + fun1(n - 4) + fun1(n - 5);
    //     fun1(n - 1) + fun1(n - 2) + fun2(n - 1) + fun2(n - 2)
    return a[n];
}
ll fun2(int n) // 到达 n 的最后一次是跳三步的
{
    if (n <= 0)
        return 0;
    return fun1(n - 3);
}
int main()
{
    int n;
    while (~scanf("%d", &n))
    {
        printf("%lld\n", fun1(n) + fun2(n));
    }
    return 0;
}
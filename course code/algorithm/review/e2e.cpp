#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;
const int MS = 1e4 + 5;
int sum[MS];
int ans[MS];
int main()
{
    int n, m;
    int a;
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++)
    {
        scanf("%d", &a);
        sum[i] = sum[i - 1] + a;
    }
    int ma = -2147483648;
    int an = ma;
    for (int i = n; i >= 1; i--)
    {
        for (int j = 1; j + i - 1 <= n; j++)
        {
            int r = j + i - 1;
            an = max(an, sum[r] - sum[j - 1]);
        }
        ans[i] = max(an, ma);
        ma = ans[i];
    }

    while (m--)
    {
        scanf("%d", &an);
        printf("%d\n", ans[an]);
    }
    return 0;
}
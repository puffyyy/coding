#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <cstdlib>
#include <algorithm>
using namespace std;
const int MS = 1e5 + 5;
int a[MS], b[MS];
int main()
{

    int n, m;
    cin >> n >> m;
    for (int i = 1; i <= n; ++i)
    {
        scanf("%d", &a[i]);
    }
    int l, r, flag;
    while (m--)
    {
        flag = 0;
        scanf("%d%d", &l, &r);
        if (r - l >= 48)
        {
            printf("Yes\n");
            continue;
        }
        for (int i = l; i <= r; ++i)
            b[i] = a[i];
        sort(b + l, b + r + 1);
        for (int i = l + 1; i < r; ++i)
        {
            if (b[i + 1] - b[i] < b[i - 1])
            {
                flag = 1;
                break;
            }
        }
        if (flag)
            printf("Yes\n");
        else
            printf("No\n");
    }
    return 0;
}
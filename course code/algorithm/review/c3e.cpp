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
typedef long long ll;
const int MS = 500 + 5;
int p[MS], q[MS];
ll e[MS][MS], w[MS][MS];
int main()
{
    int n;
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%d", p + i);
    for (int i = 0; i <= n; i++)
        scanf("%d", q + i);
    for (int i = 1; i <= n + 1; i++)
    {
        w[i][i - 1] = q[i - 1];
        e[i][i - 1] = q[i - 1];
    }
    for (int l = 1; l <= n; l++)
        for (int i = 1; i <= n - l + 1; i++)
        {
            int j = i + l - 1;
            e[i][j] = 132663314541612;
            w[i][j] = w[i][j - 1] + p[j] + q[j];
            for (int r = i; r <= j; r++)
            {
                int t = e[i][r - 1] + e[r + 1][j] + w[i][j];
                if (t < e[i][j])
                    e[i][j] = t;
            }
        }
    printf("%lld", e[1][n]);
    return 0;
}
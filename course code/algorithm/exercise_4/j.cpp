#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <cstdlib>
#include <algorithm>
using namespace std;
typedef long long int ll;
const int MS = 1e6 + 5;
int a[MS], b[MS];
int n, m;
int getmid(int a[], int la, int b[], int lb, int k)
{
    if (la >= n)
        return b[lb + k - 1];
    if (lb >= m)
        return a[la + k - 1];
    if (k == 1)
    {
        return min(a[la], b[lb]);
    }
    int Vala = (la + k / 2 - 1 < n) ? a[la + k / 2 - 1] : 1 << 10;
    int Valb = (lb + k / 2 - 1 < m) ? b[lb + k / 2 - 1] : 1 << 10;
    if (Vala < Valb)
    {
        return getmid(a, la + k / 2, b, lb, k - k / 2);
    }
    else
    {
        return getmid(a, la, b, lb + k / 2, k - k / 2);
    }
}
int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 0; i < n; i++)
        scanf("%d", a + i);
    for (int i = 0; i < m; i++)
        scanf("%d", b + i);
    {
        int ll = getmid(a, 0, b, 0, (m + n + 1) / 2);
        int rr = getmid(a, 0, b, 0, (m + n + 2) / 2);
        printf("%.2lf", 1.0 * (ll + rr) / 2);
    }
    return 0;
}

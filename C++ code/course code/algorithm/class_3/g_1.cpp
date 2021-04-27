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
const int MS = 3e2 + 5;
int a[MS], b[MS], t[MS];
int c[MS], v[MS];
int n, m;
int ans;
int main()
{
    scanf("%d%d", &n, &m);
    m *= 12;
    for (int i = 1; i <= n; i++)
        scanf("%d", a + i);
    for (int i = 1; i <= n; i++)
        scanf("%d", b + i);
    for (int i = 2; i <= n; i++)
        scanf("%d", t + i);
    int sumt = m, va, vb, j, pos, sum;
    for (int i = 1; i <= n; i++)
    {
        sumt -= t[i];
        va = a[i], vb = b[i];
        j = pos = 1;
        while (pos <= sumt)
        {
            if (v[j] < va)
                c[pos++] = va, va = (va - vb > 0 ? va - vb : 0);
            else
                c[pos++] = v[j++];
        }
        sum = 0;
        for (int i = 1; i <= sumt; i++)
        {
            v[i] = c[i];
            sum += c[i];
        }
        ans = ans < sum ? sum : ans;
    }
    printf("%d", ans);
    return 0;
}
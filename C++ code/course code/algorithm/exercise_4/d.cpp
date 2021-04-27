#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <cstdlib>
#include <algorithm>
using namespace std;
typedef long long int ll;
const int MS = 1e3 + 5;
int a[MS];
int tmp[MS];
int len;
int main()
{
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
    {
        scanf("%d", a + i);
        a[n + i] = a[i];
    }
    int ans = MS;
    int pos;
    for (int i = 0; i < n; i++)
    {
        len = 0;
        for (int j = i; j < n + i; j++)
        {
            if (a[j] > tmp[len])
                tmp[++len] = a[j];
            else
            {
                pos = upper_bound(tmp, tmp + len, a[j]) - tmp;
                tmp[pos] = a[j];
            }
        }
        ans = min(n - len, ans);
    }
    printf("%d", ans);
    return 0;
}
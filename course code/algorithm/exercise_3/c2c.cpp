#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;
const int MS = 1e5 + 5;
int a[MS], c[MS];
int LIS(int a[], int len)
{
    int top = 0;
    for (int i = 1; i <= len; i++)
    {
        int pos = lower_bound(c, c + top, a[i]) - c;
        c[pos] = a[i];
        top = top + (pos == top ? 1 : 0);
    }
    return top;
}
int main()
{
    int n;
    scanf("%d", &n);
    int tmp;
    for (int i = 1; i <= n; i++)
    {
        scanf("%d", &tmp);
        c[tmp] = i;
    }
    for (int i = 1; i <= n; i++)
    {
        scanf("%d", &tmp);
        a[i] = c[tmp];
    }
    printf("%d", LIS(a, n));
    return 0;
}
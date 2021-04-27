#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MIN(a, b) ((a) < (b) ? (a) : (b))
long long a[32] = {1, 1, 2, 5, 14, 42};
extern long long fun(int n);
long long cal(int n)
{
    if (a[n] != 0)
        return a[n];
    else
        return a[n] = fun(n);
}
long long fun(int n)
{
    long long ans = 0;
    if (a[n] != 0)
        return a[n];
    for (int i = 0; i <= n - 1; i++)
    {
        ans += cal(i) * cal(n - i - 1);
    }
    return ans;
}
int main()
{

    int n;
    scanf("%d", &n);
    printf("%lld", fun(n));
    return 0;
}
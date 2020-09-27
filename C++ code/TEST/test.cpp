#include <stdio.h>
#include <stdlib.h>
int a[60] = {1, 1, 1};
int fun(int n)
{
    if (a[n] != 0)
        return a[n];
    return a[n] = fun(n - 1) + fun(n - 2);
}
int main()
{
    int n, i;
    scanf("%d", &n);
    printf("%d", fun(n));
    return 0;
}
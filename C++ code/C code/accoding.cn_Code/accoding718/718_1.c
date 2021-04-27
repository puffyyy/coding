#include <stdio.h>
long long a[755];
int main()
{
    int n;
    while (~scanf("%d", &n))
    {
        a[1] = 1, a[0] = 1, a[2] = 3, a[3] = 5, a[4] = 11;
        for (int i = 2; i <= n / 3; i++)
        {
            a[i] = (a[i - 1] + 2 * a[i - 2]);
        }
        printf("%lld\n", (a[n / 3]));
    }
}
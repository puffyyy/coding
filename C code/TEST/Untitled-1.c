#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
int a[10005][6];
int main()
{
    int t;
    int n, m;
    scanf("%d", &t);
    while (t--)
    {
        scanf("%d%d", &n, &m);
        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++)
            {
                scanf("%d", &a[i][j]);
            }

        long long ans = 0x80000000;

        for (int j = 0; j < (1 << m); j++)
        {
            long long mi = 0x80000000;
            long long ni = 0x7fffffff;
            for (int i = 0; i < n; i++)
            {
                int x = j;
                long long s = 0;
                for (int k = 0; k < m; k++)
                {
                    if (x & 1)
                        s += a[i][k];
                    else
                        s -= a[i][k];
                    x >>= 1;
                }
                if (mi < s)
                    mi = s;
                if (ni > s)
                    ni = s;
            }
            ans = ans > mi - ni ? ans : mi - ni;
        }
        printf("%lld\n", ans);
    }
}
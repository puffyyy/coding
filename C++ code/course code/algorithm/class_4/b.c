#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

int main()
{
    int k;
    int n = 1;
    int cnt;
    while (scanf("%d", &k) != EOF)
    {
        n = cnt = 1;
        if (k % 2 == 0 || k % 5 == 0)
        {
            printf("-1\n");
            continue;
        }
        if (k % 7 == 0)
            k /= 7;
        while (n % k)
        {
            ++cnt;
            n = (n % k) * 10 + 1;
        }
        printf("%d\n", cnt);
    }
    return 0;
}
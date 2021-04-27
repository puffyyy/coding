#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

int a[1005];
int b[1005];
int main()
{
    int n, k;
    int x, y;
    scanf("%d%d", &n, &k);
    for (int i = 0; i < k; i++)
    {

        scanf("%d %d", &x, &y);
        a[y]++;
        b[x]++;
    }
    for (int i = 0; i <= n; i++)
    {
        if (a[i] == n - 1 && b[i] == 0)
        {
            printf("%d\n", i);
            return 0;
        }
    }
    printf("-1\n");
    return 0;
}
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
int a[10000007] = {1};
int num, ch[20];
int main()
{
    int n;
    scanf("%d", &n);
    printf("1 ");
    register int i = 1, j = 0, cnt = 1;
    for (; i < n; ++i)
    {
        ++j;
        if (j == cnt)
        {
            j = 0;
            cnt <<= 1;
            a[i] = 1;
        }
        else
        {
            a[i] = a[i - cnt] + 1;
        }
        printf("%d ", a[i]);
    }
    return 0;
}
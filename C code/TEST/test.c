#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
void split(int x)
{
    int i;
    long long j;
    while (x)
    {
        for (i = 0, j = 1; j * 3 <= 1LL * x; j *= 3, i++)
            ;
        if (j <= 3)
            printf("%d", j);
        else
        {
            printf("3(");
            split(i);
            printf(")");
        }
        x -= j;
        if (x)
            printf("+");
    }
}
int main()
{
    int n;
    scanf("%d", &n);
    split(n);
    return 0;
}
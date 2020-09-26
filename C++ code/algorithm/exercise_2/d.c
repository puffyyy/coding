#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

long long ans[51], b[51];

int main()
{
    int n;
    b[0] = 1;
    ans[0] = 1;
    ans[1] = 1;
    b[1] = 1;
    b[2] = 2;
    ans[2] = 2;
    for (int i = 3; i < 51; ++i)
    {
        b[i] = ans[i - 1] + ans[i - 2]; //到达n的最后一次只跳 1 2的
        ans[i] = b[i] + b[i - 3];
    }
    while (~scanf("%d", &n))
        printf("%lld\n", ans[n]);
    return 0;
}
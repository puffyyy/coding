#include <stdio.h>
#include <stdlib.h>
int data[24];
int res[10000007];
int main()
{
    int n, N, i = 23, j, cnt = 0;
    scanf("%d", &N);
    n = N;
    while (N > 0)
    {
        data[i--] = N % 2;
        if (data[i + 1] == 1)
            cnt++;
        N /= 2;
    }
    res[n] = cnt;
    for (i = n - 1; i >= 1; i--)
    {
        data[23]--;
        if (data[23] == 0)
            res[i] = cnt - 1;
        else
        {
            cnt = 0;
            for (j = 23; j > 0; j--)
                if (data[j] < 0)
                {
                    data[j] += 2;
                    data[j - 1] -= 1;
                }
            for (j = 23; j >= 0; j--)
                if (data[j] == 1)
                    cnt++;
            res[i] = cnt;
        }
    }
    for (i = 1; i < n; i++)
        printf("%d ", res[i]);
    printf("%d\n", res[i]);
    return 0;
}
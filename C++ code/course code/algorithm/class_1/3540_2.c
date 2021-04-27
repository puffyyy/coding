#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

int cmp(const void *a, const void *b)
{
    int *c = (int *)a;
    int *d = (int *)b;
    if (*c - *d < 0)
        return 1;
    else
        return -1;
}
#define MAXSIZE 10000005
int arr[MAXSIZE];
int main()
{
    int t;
    scanf("%d", &t);
    while (t--)
    {
        int k, n;
        scanf("%d%d", &n, &k);
        for (int i = 0; i < n; i++)
            scanf("%d", &arr[i]);
        qsort(arr, n, sizeof(arr[0]), cmp);
        printf("%d\n", arr[k - 1]);
    }
    return 0;
}
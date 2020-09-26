#include <stdio.h>
#include <stdlib.h>
int a[200005];
int cmp(const void *a, const void *b)
{
    int *c = (int *)a;
    int *d = (int *)b;
    return *c - *d;
}
int main()
{
    int n, k;
    while (~scanf("%d%d", &n, &k))
    {
        int l, r, ans = 0;
        for (int i = 0; i < k; ++i)
        {
            scanf("%d%d", &a[i], &a[k + i]);
            ++a[k + i];
        }
        qsort(a, 2 * k, sizeof(a[0]), cmp);
        for (int i = 1; i < 2 * k; ++i)
            if (i & 1 == 1)
                ans += a[i] - a[i - 1];
        printf("%d\n", ans);
    }
    return 0;
}

/*
8 3
0 6 3 7 2 4
*/

/*
8 3
0 7
2 4
3 7
*/
#include <stdio.h>
#include <stdlib.h>
#define MAXSIZE 100005
int a[MAXSIZE], b[MAXSIZE];
int cmp(const void *a, const void *b)
{
    int *c = (int *)a;
    int *d = (int *)b;
    if (*c - *d > 0)
        return 1;
    else
        return -1;
}
int main()
{
    int n, k;
    while (~scanf("%d%d", &n, &k))
    {
        for (int i = 0; i < k; ++i)
        {
            scanf("%d%d", &a[i], &b[i]);
        }
        qsort(a, k, sizeof(a[0]), cmp);
        qsort(b, k, sizeof(b[0]), cmp);
        int l = 0, r = 0;
        int ans = 0, min;
        a[k] = b[k] = MAXSIZE;
        for (int i = a[0]; i <= b[k - 1]; ++i)
        {
            while (a[l] <= i && l < k)
                ++l;
            while (b[r] < i && r < k)
                ++r;
            if ((l - r) & 1 == 1)
            {
                min = a[l] > b[r] + 1 ? b[r] + 1 : a[l];
                ans += min - i;
                // printf("%d->", i);
                i = i > min - 1 ? i : min - 1;
                // printf("%d\n", i);
            }
        }
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
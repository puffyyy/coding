#include <stdio.h>
#include <stdlib.h>
#define size 100002

struct edge
{
    int x, y, z;
} e[size];
int pre[size], num[size];
long long ans;
int cmp(const void *a, const void *b)
{
    struct edge *c = (struct edge *)a;
    struct edge *d = (struct edge *)b;
    return c->z - d->z;
}
int find(int x)
{
    if (pre[x] != x)
        pre[x] = find(pre[x]);
    return pre[x];
}
int main()
{
    int t, n;
    scanf("%d", &t);
    while (t--)
    {
        ans = 0;
        scanf("%d", &n);
        for (int i = 1; i < n; i++)
        {
            scanf("%d%d%d", &e[i].x, &e[i].y, &e[i].z);
            ans += e[i].z;
        }
        for (int i = 1; i <= n; i++)
        {
            pre[i] = i;
            num[i] = 1;
        }
        qsort(e + 1, n - 1, sizeof(e[0]), cmp);
        for (int i = 1; i < n; i++)
        {
            int fx = find(e[i].x), fy = find(e[i].y);
            if (fx != fy)
            {
                pre[fx] = fy;
                ans += (long long)(e[i].z + 1) * (long long)(num[fx] * num[fy] - 1); //必须longlong
                num[fy] += num[fx];
                num[fx] = 0;
            }
        }
        printf("%lld\n", ans);
    }

    return 0;
}
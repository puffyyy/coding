#include <cstdio>
int main()
{
    int t, n, m;
    scanf("%d", &t);
    while (t--)
    {
        scanf("%d%d", &n, &m);
        if (n == 0 || m == 0 || m == 1)
        {
            printf("%d\n", m);
            continue;
        }
        int pre = 0, now = m;
        for (int i = 1; i <= n; i++)
        {
            now += pre;
            pre = now / 2;
        }
        printf("%d\n", pre + now);
    }
    return 0;
}
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
using namespace std;
struct
{
    int l, r;
} op[16];
int a[60];
int ans, t, n;
void init()
{
    for (int i = 1; i <= n; i++)
        a[i] = i;
    return;
}
void dfs(int deepth)
{
    if (!deepth)
    {
        ++ans;
        return;
    }
    int l = op[deepth].l, r = op[deepth].r;
    if (a[l] > a[r])
        return;
    dfs(deepth - 1);
    swap(a[l], a[r]);
    dfs(deepth - 1);
    swap(a[l], a[r]);
}

int main()
{
    register int i, j, k;
    scanf("%d", &t);
    while (t--)
    {
        ans = 0;
        scanf("%d%d", &n, &k);
        for (i = 1; i <= k; i++)
            scanf("%d%d", &op[i].l, &op[i].r);
        for (i = 1; i <= n; ++i)
        {
            init();
            for (j = i; j > 1; --j)
            {
                swap(a[j], a[j - 1]);
                if (i != 1 && j == i)
                    continue;
                dfs(k);
            }
            init();
            for (j = i; j < n; ++j)
            {
                swap(a[j], a[j + 1]);
                dfs(k);
            }
        }
        init(), dfs(k);

        printf("%d\n", ans);
    }

    return 0;
}
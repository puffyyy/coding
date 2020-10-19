#include <stdio.h>
#include <stdlib.h>
struct
{
    int l, r;
} op[16];
int a[51], ans;
void Dfs(int level)
{
    if (level == 0) //current list pass the filter
    {
        ++ans;
        return;
    }
    int l = op[level].l - 1, r = op[level].r - 1;
    if (a[l] > a[r]) //left > right:illegal list
        return;      //list should be sorted
    Dfs(level - 1);  //not swap
    Swap(l, r);
    Dfs(level - 1); //swap
    Swap(l, r);     //recover
}
void Swap(int i, int j)
{
    int tmp = a[i];
    a[i] = a[j];
    a[j] = tmp;
}
void init(int n)
{
    for (int i = 0; i < n; i++)
        a[i] = i + 1;
    return;
}
int main()
{
    int t, n, k, i, j;
    scanf("%d", &t);
    while (t--)
    {
        ans = 0;
        scanf("%d%d", &n, &k);
        for (i = 1; i <= k; i++)
            scanf("%d%d", &op[i].l, &op[i].r);
        for (i = 0; i < n; i++) //change location for a[i] (i+1)
        {
            init(n);
            for (j = i; j > 0; j--) //change left
            {
                Swap(j, j - 1);
                if (i > 0 && j == i) //avoid repeat list
                    continue;
                Dfs(k);
            }

            init(n);
            for (j = i; j < n - 1; j++)
            {
                Swap(j, j + 1);
                Dfs(k);
            }
        }
        init(n);
        Dfs(k); //test if the ordered list ober the filter

        printf("%d\n", ans);
    }
    return 0;
}

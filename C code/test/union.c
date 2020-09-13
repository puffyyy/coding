#include <stdio.h>
#define MAXSIZE 200002
int visit[MAXSIZE];
long long tr[MAXSIZE];
void init(int n)
{
    for (int i = 0; i < n; i++)
    {
        tr[i] = i;
    }
}
int find(int x)
{
    int s = x;
    for (; tr[s] != s; s = tr[s])
        ;
    /*
    int tmp;
    while (s != x)
    {
        tmp = tr[x];
        tr[x] = s;
        x = tmp;
    }
    */
    return tr[x] = s;
}
void union_(int a, int b)
{
    int r1 = find(a), r2 = find(b);
    if (r1 == r2)
        return; //已经在一个集合里了
    tr[r1] = r2;
}
int main()
{
    int n, m;
    scanf("%d%d", &n, &m);
    int ans = n;
    init(n);
    for (int i = 0; i < m; i++)
    {
        int a, b;
        scanf("%d%d", &a, &b);
        for (int j = a; j <= b; j++)
        {
            if (visit[j] == 1)
                j = find(j);
            else
            {
                visit[j] = 1;
                ans--;
            }
            union_(j, b);
        }
        printf("%d\n", ans);
    }
    return 0;
}
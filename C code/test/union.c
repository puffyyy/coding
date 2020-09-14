#include <stdio.h>
#define MAXSIZE 200002
int visit[MAXSIZE];
int tr[MAXSIZE];
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
    tr[a] = b;
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
            {
                int tmp = j;
                j = find(j);
                union_(tmp, b);
            }
            else
            {
                visit[j] = 1;
                union_(j, b);
                ans--;
            }
        }
        printf("%d\n", ans);
    }
    return 0;
}
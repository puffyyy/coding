#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <cstdlib>
using namespace std;
const int MS = 1e5 + 5;
int n;
int a[MS], b[MS];
char path[MS];
bool visit[MS];
int top;
bool dfs(int x)
{
    static bool flag = 0;
    if (flag || visit[x])
        return 0;
    if (x < 1 || x > n)
        return 0;
    if (x == n)
    {
        int pos = 1;
        memset(visit, 0, sizeof(visit));
        visit[pos] = 1;
        for (int i = 0; i < top; i++)
        {
            if (path[i] == 'a')
                pos += a[pos];
            else
            {
                if (visit[pos + a[pos]] == 1)
                {
                    printf("Infinity!\n");
                    return 1;
                }
                else
                    pos += b[pos];
            }
            visit[pos] = 1;
        }
        for (int i = 0; i < top; i++)
            putchar(path[i]);
        putchar('\n');
        return 1;
    }
    visit[x] = 1;

    path[top++] = 'a';
    flag |= dfs(x + a[x]);
    --top;
    path[top++] = 'b';
    flag |= dfs(x + b[x]);
    --top;
    return flag;
}
int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%d", a + i);
    for (int i = 1; i <= n; i++)
        scanf("%d", b + i);
    if (!dfs(1))
        printf("No solution!");
    return 0;
}
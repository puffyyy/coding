#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <cstdlib>
#include <algorithm>
using namespace std;
typedef long long ll;
const int MS = 1e5 + 5;
bool visit[MS];
int a[MS], b[MS];
int str[MS];
int n, len = 0;
bool check()
{
    int pos = 1;
    memset(visit, 0, sizeof(visit));
    for (int i = 0; i < len; i++)
    {
        if (str[i])
            pos += a[pos];
        else
        {
            if (visit[pos + a[pos]] == 1)
                return 0;
        }
        visit[pos] = 1;
    }
    return 1;
}
bool dfs(int pos)
{
    static bool flag = 0;
    if (flag)
        return 0;
    if (pos <= 0 || pos > n)
        return 0;
    if (visit[pos])
        return 0;
    if (pos == n)
    {
        flag = 1;
        if (check())
            for (int i = 0; i < len; i++)
                printf("%c", str[i] ? 'a' : 'b');
        else
            printf("Infinity!");
        return 1;
    }
    visit[pos] = 1;
    str[len++] = 1;
    flag |= dfs(pos + a[pos]);
    len--;
    str[len++] = 0;
    flag |= dfs(pos + b[pos]);
    len--;
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
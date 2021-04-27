#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
using namespace std;
char a[330][330];
int x, y;
void move(int lr, int ud)
{
    int xt = x + lr, yt = y + ud;
    if (a[xt][yt] == '*')
    {
        a[x][y] = '*';
        a[xt][yt] = 'P';
        x = xt, y = yt;
    }
    else if (a[xt][yt] == 'B' && a[xt + lr][yt + ud] == '*')
    {
        a[xt + lr][yt + ud] = 'B';
        a[x][y] = '*';
        a[xt][yt] = 'P';
        x = xt, y = yt;
    }
    return;
}
int main()
{
    int m, n;
    scanf("%d%d\n", &n, &m);
    for (int i = 1; i <= n; ++i)
        scanf("%s", (a[i] + 1));
    for (int i = 0; i <= m + 1; i++)
    {
        a[0][i] = 'W', a[n + 1][i] = 'W';
    }
    for (int i = 0; i <= n + 1; ++i)
    {
        a[i][0] = 'W', a[i][m + 1] = 'W';
    }

    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= m; ++j)
        {
            if (a[i][j] == 'P')
            {
                x = i, y = j;
                break;
            }
        }
    char mod[1000005];
    scanf("%s", mod);
    for (int i = 0; mod[i] != '\0'; ++i)
    {
        switch (mod[i])
        {
        case 'A':
            move(-1, 0);
            break;
        case 'B':
            move(1, 0);
            break;
        case 'L':
            move(0, -1);
            break;
        case 'R':
            move(0, 1);
            break;
        }
    }
    for (int i = 1; i <= n; ++i)
    {
        for (int j = 1; j <= m; ++j)
            printf("%c", a[i][j]);
        printf("\n");
    }
    return 0;
}
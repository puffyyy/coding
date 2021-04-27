#include <iostream>
#include <cstdio>
using namespace std;
int n;
int a[2050], b[2050];
bool recur(int x, int y)
{
    if (a[x] == b[y])
    {
        if ((x << 1) > n && (y << 1) > n)
            return true;
        else
            return (recur(x << 1, y << 1) && recur((x << 1) + 1, (y << 1) + 1)) || (recur(x << 1, (y << 1) + 1) && recur((x << 1) + 1, y << 1));
    }
    else
        return false;
}
int main()
{
    int t, k;
    scanf("%d", &t);
    while (t--)
    {
        n = 1;
        scanf("%d", &k);
        for (int i = 0, size = 1; i <= k; ++i)
        {
            size <<= 1;
            for (; n < size; ++n)
                scanf("%d", &a[n]);
        }
        n = 1;
        for (int i = 0, size = 1; i <= k; ++i)
        {
            size <<= 1;
            for (; n < size; ++n)
                scanf("%d", &b[n]);
        }
        n -= 1;
        if (recur(1, 1))
            printf("Yes\n");
        else
            printf("No\n");
    }
    return 0;
}
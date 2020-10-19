#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include <stack>
#include <queue>
#include <set>
using namespace std;
typedef long long int ll;
const int MS = 5e5 + 5;
char str[MS << 1];
int sa[MS];
int rk[MS << 1];
int oldrk[MS << 1];
int w;
void calSA(char str[], int len)
{
    int i, p, n = len;
    for (i = 1; i <= n; ++i)
        str[n + i] = str[i];
    for (i = 1; i <= 2 * n; ++i)
        sa[i] = i, rk[i] = str[i];

    for (w = 1; w < n; w <<= 1)
    {
        sort(sa + 1, sa + 2 * n + 1, [](int x, int y) {
            return rk[x] == rk[y] ? rk[x + w] < rk[y + w] : rk[x] < rk[y];
        }); // 这里用到了 lambda
        memcpy(oldrk, rk, sizeof(int) * (2 * n + 5));
        // 由于计算 rk 的时候原来的 rk 会被覆盖，要先复制一份
        for (p = 0, i = 1; i <= 2 * n; ++i) //去重
        {
            if (oldrk[sa[i]] == oldrk[sa[i - 1]] &&
                oldrk[sa[i] + w] == oldrk[sa[i - 1] + w])
            {
                rk[sa[i]] = p;
            }
            else
            {
                rk[sa[i]] = ++p;
            } // 若两个子串相同，它们对应的 rk 也需要相同，所以要去重
        }
    }
}
int main()
{
    //ios::sync_with_stdio(false);
    int t, len;
    scanf("%d", &t);
    while (t--)
    {
        scanf("%s", str + 1);
        len = strlen(str + 1);
        calSA(str, len);
        int pos;
        for (pos = 1; pos <= len; pos++)
        {
            if (sa[pos] <= len)
                break;
        }
        for (int i = sa[pos]; i <= len; ++i)
            putchar(str[i]);
        for (int i = 1; i < sa[pos]; ++i)
            putchar(str[i]);
        putchar('\n');
    }
    return 0;
}
#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <cstdlib>
#include <algorithm>
using namespace std;
typedef long long int ll;
const int MS = 1e5 + 5;
char str[MS << 1];
int sa[MS];
int rk[MS << 1];
int oldrk[MS << 1];
int id[MS], cnt[MS];
int n;
void calSA(char str[])
{
    int i, p, m, w;
    m = max(n, 256);
    memset(cnt, 0, sizeof(cnt));
    for (i = 1; i <= n; ++i)
        ++cnt[rk[i] = str[i]];
    for (i = 1; i <= m; ++i)
        cnt[i] += cnt[i - 1];
    for (i = n; i >= 1; --i) // 倒序 使 相等时 靠后的数 排名靠后
        sa[cnt[rk[i]]--] = i;
    for (w = 1; w < n; w <<= 1, m = p)
    {
        memset(cnt, 0, sizeof(cnt)); //对第二关键字排序
        for (i = 1; i <= n; ++i)
            id[i] = sa[i];
        for (i = 1; i <= n; ++i)
            ++cnt[rk[(id[i] + w) > n ? (id[i] + w) - n : (id[i] + w)]];
        for (i = 1; i <= m; ++i)
            cnt[i] += cnt[i - 1];
        for (i = n; i >= 1; --i)
            sa[cnt[rk[(id[i] + w) > n ? (id[i] + w) - n : (id[i] + w)]]--] = id[i];
        memset(cnt, 0, sizeof(cnt));
        for (i = 1; i <= n; ++i)
            id[i] = sa[i];
        for (i = 1; i <= n; ++i)
            ++cnt[rk[id[i]]];
        for (i = 1; i <= m; ++i)
            cnt[i] += cnt[i - 1];
        for (i = n; i >= 1; --i)
            sa[cnt[rk[id[i]]]--] = id[i];
        memcpy(oldrk, rk, sizeof(rk));
        for (p = 0, i = 1; i <= n; ++i)
        {
            if (oldrk[sa[i]] == oldrk[sa[i - 1]] &&
                oldrk[(sa[i] + w) > n ? (sa[i] + w) - n : (sa[i] + w)] == oldrk[(sa[i - 1] + w) > n ? (sa[i - 1] + w) - n : (sa[i - 1] + w)])
                rk[sa[i]] = p;
            else
                rk[sa[i]] = ++p;
        }
    }
}
int main()
{
    int t;
    scanf("%d", &t);
    while (t--)
    {
        scanf("%s", str + 1);
        n = strlen(str + 1);
        calSA(str);
        for (int i = sa[1]; i <= n; ++i)
            putchar(str[i]);
        for (int i = 1; i < sa[1]; ++i)
            putchar(str[i]);
        putchar('\n');
    }
    return 0;
}
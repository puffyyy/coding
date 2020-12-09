#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>

using namespace std;

const int N = 100;
char s[N];
int n, sa[N], rk[N << 1], oldrk[N << 1], id[N], cnt[N];

//基数排序优化
int main()
{
    int i, m, p, w;

    scanf("%s", s + 1);
    // 初始化
    n = strlen(s + 1);
    m = max(n, 300);
    for (i = 1; i <= n; ++i)
        ++cnt[rk[i] = s[i]];
    for (i = 1; i <= m; ++i)
        cnt[i] += cnt[i - 1];
    for (i = n; i >= 1; --i) // 倒序 使 相等时 靠后的数 排名靠后
        sa[cnt[rk[i]]--] = i;
    // for (i = 1; i <= n; ++i)
    //     sa[cnt[rk[i]]--] = i;
    for (w = 1; w < n; w <<= 1)
    {
        memset(cnt, 0, sizeof(cnt)); //对第二关键字排序
        for (i = 1; i <= n; ++i)
            id[i] = sa[i];
        for (i = 1; i <= n; ++i)
            ++cnt[rk[id[i] + w]];
        for (i = 1; i <= m; ++i)
            cnt[i] += cnt[i - 1];
        for (i = n; i >= 1; --i)
            sa[cnt[rk[id[i] + w]]--] = id[i];
        memset(cnt, 0, sizeof(cnt));
        for (i = 1; i <= n; ++i)
            id[i] = sa[i];
        for (i = 1; i <= n; ++i)
            ++cnt[rk[id[i]]];
        for (i = 1; i <= m; ++i)
            cnt[i] += cnt[i - 1];
        for (i = n; i >= 1; --i)
            sa[cnt[rk[id[i]]]--] = id[i];
        //排序
        memcpy(oldrk, rk, sizeof(rk));
        for (p = 0, i = 1; i <= n; ++i)
        {
            if (oldrk[sa[i]] == oldrk[sa[i - 1]] &&
                oldrk[sa[i] + w] == oldrk[sa[i - 1] + w])
            {
                rk[sa[i]] = p;
            }
            else
            {
                rk[sa[i]] = ++p;
            }
        }
        for (i = 1; i <= n; ++i)
            printf("%d ", rk[i]);
        putchar('\n');
    }

    for (i = 1; i <= n; ++i)
        printf("%d ", sa[i]);

    return 0;
}
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
int a[100005];
int len;
void delete_array_pos(int pos)
{
    --len;
    for (int i = pos; i < len; ++i)
    {
        a[i] = a[i + 1];
    }
}
int binarysearch(int x, int len) //小于x的个数 要求升序 下标从0开始
{
    int mid, l, r;
    l = 0, r = len;
    while (l < r)
    {
        mid = (l + r) >> 1;
        if (a[mid] < x)
            l = mid + 1;
        else
            r = mid;
    }
    return l;
}
int main()
{
    int n, m, w;
    int cnt = 0;
    scanf("%d%d%d", &n, &m, &w);
    w -= m;
    for (len = 0; len < n; ++len)
    {
        scanf("%d", a + len);
    }
    int cur;
    while (len > 0)
    {
        cur = w - a[len - 1];
        delete_array_pos(len - 1);
        while (cur > 0)
        {
            int pos = binarysearch(cur, len);
            if ((pos == 0 && len == 0))
                break;
            if (a[pos] > cur)
            {
                pos -= 1;
                if (pos >= 0 && a[pos] <= cur)
                {
                    cur -= a[pos];
                    delete_array_pos(pos);
                }
                else
                    break;
            }
            else
            {
                cur -= a[pos];
                delete_array_pos(pos);
            }
        }
        ++cnt;
    }
    printf("%d", cnt);
    return 0;
}
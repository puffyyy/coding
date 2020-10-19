#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;
const int MS = 1e5 + 5;
int a[MS];
int map[MS]; // pos <- map[i] 表示 值i 在 a序列中的位置是 pos
int f[MS];   // f 是有序的 f 存储的是当前的选择的上升序列 f[i]存储的值是 a序列中的位置
int len;     // len 是 f 当前的长度
int main()
{
    int n;
    scanf("%d", &n);
    register int i;
    for (i = 1; i <= n; ++i)
    {
        scanf("%d", a + i);
        map[a[i]] = i;
    }
    int b; //满足上升的也就是满足原串的排列顺序的
    for (i = 1; i <= n; ++i)
    {
        scanf("%d", &b);
        if (map[b] > f[len])
            f[++len] = map[b];
        else
        {
            int pos = upper_bound(f, f + len, map[b]) - f;
            f[pos] = map[b];
        }
    }
    printf("%d", len);
    return 0;
}
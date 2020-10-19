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
    int b;
    fill(f, f + n, MS);
    for (i = 1; i <= n; ++i)
    {
        scanf("%d", &b);
        *lower_bound(f, f + n, map[b]) = map[b];
    }
    printf("%d", lower_bound(f, f + n, MS) - f);
    return 0;
}
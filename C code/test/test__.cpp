#include <stdio.h>
#define MAXN 300005
int n;
int a[MAXN];
int prev[MAXN], next[MAXN]; //双向链表
int u[MAXN], v[MAXN];       //u[x]表示x的前驱，v[x]表示x的后继
int deep[MAXN];

int main(void)
{
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i)
        scanf("%d", a + i);

    for (int i = 1; i <= n; ++i)
    {
        prev[i] = i - 1; //存储前驱节点编号
        next[i] = i + 1; //存储后继节点编号
    }
    int x;
    for (int i = n; i > 1; --i) //从后往前，保证前驱后继已经出现
    {
        x = a[i]; //x为当前需要插入的值
        u[x] = prev[x];
        //如果x的prev[x]=x-1,未出现在a[i~n]中,则x的前驱就是prev[x],如果出现过，那么该节点已被删除，prev[x]为在a[1~i]中出现过的比x小的最大的数
        v[x] = next[x];
        next[prev[x]] = next[x];
        prev[next[x]] = prev[x]; //删除该节点x,位置i前的数字未出现x
    }
    for (int i = 1; i <= n; i++)

        printf("%d: [u]%d |[v]%d\n", i, u[i], v[i]);

    long long sum = 0;
    for (int i = 1; i <= n; ++i)
    {
        x = a[i];
        if ((u[x] >= 1) && (u[x] <= n))
            if (deep[x] < deep[u[x]] + 1)
                deep[x] = deep[u[x]] + 1;
        if ((v[x] >= 1) && (v[x] <= n))
            if (deep[x] < deep[v[x]] + 1)
                deep[x] = deep[v[x]] + 1;
        sum += deep[x];
        printf("%lld\n", sum);
    }
    return 0;
}
// 8
// 3 5 1 6 8 7 2 4

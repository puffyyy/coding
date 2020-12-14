// 未离散化
#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;
typedef long long int ll;

int n;
const int maxn = 100010;
ll a[maxn], b[maxn], c[maxn], tree[maxn]; //对应原数组和树状数组

int lowbit(int x)
{
    return x & (-x);
}

void update(int i, int k)
{
    //在i位置加上k
    while (i <= n)
    {
        tree[i] += k;
        i += lowbit(i);
    }
}

int getsum(int i)
{
    //求A[1 - i]的和 左闭右闭区间
    int res = 0;
    while (i > 0)
    {
        res += tree[i];
        i -= lowbit(i);
    }
    return res;
}

int main()
{

    ll ans = 0;
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i)
    {
        cin >> a[i];
        b[i] = a[i];
    }
    sort(a + 1, a + 1 + n);
    for (int i = 1; i <= n; ++i)
    {
        c[i] = lower_bound(a + 1, a + n + 1, b[i]) - a;
    }
    /*将a排序后就可以知道所以数字在整个数组中所的大小相对位置，然后对于每一个b[i]，通过二分法在a中查找它的位置，然后存到c里，就实现了数据的离散化处理*/
    /*
    for (int i = n; i >= 1; --i)
    {
        ans += getsum(c[i]);
        update(c[i], 1);
        // 计算序列的逆序数 
        // 原插入序列的倒序插入
        // 这样我们需要检测的是时间在它后面但是值比它小的数有多少
        // 很显然这是一个前缀和sum(a[i]-1)
    }
    */
    for (int i = 1; i <= n; i++)
    {
        update(c[i], 1);
        ans += i - getsum(c[i]);
        /*
        从1到n枚举，每个枚举的位置i对于总的逆序对数贡献的大小为他前面的权值大于他的权值的数的个数。
        所以我们新建一个tag数组，每个数被遍历到的时候就让相应位置的值变为1
        表示i的权值已经出现过了，即1代表有，0代表没有
        那么到了后面就可以直接查询从1到i的权值的位置的总和
        返回的值就是从1到i小于它的权值的树有几个，再通过单步容斥即可得到该位置的逆序数对数。
        */
    }

    cout << ans << endl;
    return 0;
}
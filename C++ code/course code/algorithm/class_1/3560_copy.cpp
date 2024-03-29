#include <cstdio>
#include <algorithm>
#include <cmath>
#include <iostream>
#include <cstring>
using namespace std;
const int N = 1e5 + 5;
const int inf = 0x3f3f3f3f;
struct Node
{
    int x, y, z;
    long long cnt;
} node[N];
inline bool rule_xyz(Node x, Node y)
{
    if (x.x != y.x)
        return x.x < y.x;
    if (x.y != y.y)
        return x.y < y.y;
    return x.z < y.z;
}
inline bool rule_yzx(Node x, Node y)
{
    if (x.y != y.y)
        return x.y < y.y;
    if (x.z != y.z)
        return x.z < y.z;
    return x.x < y.x;
}
int n, m, a[N], b[N];

struct BIT
{
    int w[N];
    void update(int x, int d)
    {
        while (x <= n)
        {
            w[x] += d;
            x += x & -x;
        }
    }
    int getsum(int x)
    {
        int res = 0;
        while (x)
        {
            res += w[x];
            x -= x & -x;
        }
        return res;
    }
} bit;

void cdq(int L, int R)
{
    if (L >= R)
        return;
    int mid = L + ((R - L) >> 1);
    cdq(L, mid);
    cdq(mid + 1, R);
    sort(node + L, node + mid + 1, rule_yzx);
    sort(node + mid + 1, node + R + 1, rule_yzx);
    int j = mid + 1;
    for (int i = L; i <= mid; ++i)
    {
        while (j <= R && node[j].y < node[i].y) // j 在 i 前面出现 i在j后面出现 寻找比 node[i].z 大的
        {
            bit.update(node[j].z, 1);
            ++j;
        }
        node[i].cnt += bit.getsum(n) - bit.getsum(node[i].z); //node[i].z值 后面 到 n 的逆序对 比node[i].z大的有多少
        //位置出现在 i 前面 比node[i].z大的
        //因为 j<i 当 i+1 时 之前的 j 还会小于 i+1
    }
    while (--j >= mid + 1) //撤回影响 每个 j 都被加了一遍
    {
        bit.update(node[j].z, -1);
    }

    j = R;
    for (int i = mid; i >= L; --i)
    {
        while (j >= mid + 1 && node[j].y > node[i].y) // j 在 i 后面出现 i在j前面出现 寻找比 node[i].z 小的
        {
            bit.update(node[j].z, 1);
            --j;
        }
        node[i].cnt += bit.getsum(node[i].z - 1);
    }
    while (++j <= R)
    {
        bit.update(node[j].z, -1);
    }
}
// Node x:删去的顺序 y:读入顺序 即在序列中的位置 z:值
int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; ++i)
    {
        scanf("%d", &a[i]);
        b[a[i]] = i;
    }
    for (int i = 1; i <= n; ++i)
        node[i] = (Node){inf, i, a[i], 0};
    for (int i = 1, x; i <= m; ++i)
    {
        scanf("%d", &x);
        node[b[x]].x = i; //注意审题哦 这里是删掉为x的值
    }

    sort(node + 1, node + n + 1, rule_xyz);
    //先按 x 删除顺序 排序后，分治过程中就可以忽略 删除顺序 的影响
    cdq(1, n);

    /*
    计算序列的逆序数 
    原插入序列的倒序插入
    这样我们需要检测的是时间在它后面但是值比它小的数有多少
    很显然这是一个前缀和sum(a[i]-1)
    */

    long long ans = 0;
    for (int i = n; i >= 1; --i)
    {
        //先求和 再插入 保证sum不包含自己
        ans += bit.getsum(a[i]); //原数组a[i]
        bit.update(a[i], 1);
    }

    sort(node + 1, node + n + 1, rule_xyz); //保证前m
    for (int i = 1; i <= m; ++i)
    {
        printf("%lld\n", ans);
        ans -= node[i].cnt;
    }
    return 0;
}
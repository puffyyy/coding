// 未离散化
#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;
typedef long long int ll;

int n;
ll a[100005], tree[100005]; //对应原数组和树状数组

int lowbit(int x)
{
    return x & (-x);
}

void updata(int i, int k)
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
    //求A[1 - i]的和
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
    }
    for (int i = n; i >= 1; --i)
    {
        ans += getsum(a[i]);
        updata(a[i], 1);
    }
    cout << ans << endl;
    return 0;
}
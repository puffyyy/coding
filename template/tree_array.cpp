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
const int MS = 1e5 + 5;
int n;
int tree[MS];
int lowbit(int x) { return x & (-x); }
void update(int i, int k)
{
    while (i <= n) //在i位置加上k
    {
        tree[i] += k;
        i += lowbit(i);
    }
}
int getsum(int i)
{
    int res = 0; //求A[1 - i]的和
    while (i > 0)
    {
        res += tree[i];
        i -= lowbit(i);
    }
    return res;
}
int main()
{

    return 0;
}
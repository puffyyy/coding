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
typedef long long ll;
const int MS = 1e6 + 5;
int a[MS];
int main()
{
    //ios::sync_with_stdio(false);
    //cin.tie(nullptr);
    int n;
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%d", a + i);
    int mi = 2147483647;
    int ans = 0;
    for (int i = 1; i <= n; i++)
    {
        if (a[i] - mi > ans)
            ans = a[i] - mi;
        if (mi > a[i])
            mi = a[i];
    }
    printf("%d", ans);
    return 0;
}
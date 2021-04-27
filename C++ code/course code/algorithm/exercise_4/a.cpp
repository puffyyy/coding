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
const int MS = 1e6 + 5;
int a[MS];

int main()
{
    int n, x;
    //ios::sync_with_stdio(false);
    scanf("%d", &n);
    for (int i = 0; i <= n; i++)
        scanf("%d", a + i);
    scanf("%d", &x);
    ll ans = a[0] % 1004535809;
    for (int i = 1; i <= n; i++)
    {
        ans = (ans * x % 1004535809 + a[i]) % 1004535809;
    }
    printf("%d", ans);
    return 0;
}
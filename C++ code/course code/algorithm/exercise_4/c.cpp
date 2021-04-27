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

ll dp[MS] = {1, 1, 2};
ll recu(int n)
{
    if (dp[n] != 0)
        return dp[n];
    if (n <= 0)
        return 0;
    ll ans = 0;
    for (int i = 0; i < n; ++i)
        ans += recu(i) * recu(n - 1 - i);
    return dp[n] = ans;
}
int main()
{
    //ios::sync_with_stdio(false);
    int n;
    scanf("%d", &n);
    printf("%lld", recu(n));
    return 0;
}
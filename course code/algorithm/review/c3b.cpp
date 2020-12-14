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
const int MS = 1e5 + 5;

int a[MS], dp[MS];
int main()
{
    //ios::sync_with_stdio(false);
    //cin.tie(nullptr);
    int n, ans;
    cin >> n;
    for (int i = 1; i <= n; i++)
    {
        cin >> a[i];
    }
    for (int l = 1; l <= n; l++)
    {
        ans = a[l];
        for (int i = 1; i <= l / 2; i++)
        {
            ans = max(ans, dp[i] + dp[l - i]);
        }
        dp[l] = ans;
    }
    printf("%d", dp[n]);
    return 0;
}
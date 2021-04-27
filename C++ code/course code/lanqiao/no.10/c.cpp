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
int dp[50];
int w[10];
int ans[7];
int main()
{
    //ios::sync_with_stdio(false);
    //cin.tie(nullptr);

    for (int week = 0; week < 7; week++)
    {

        for (int times = 1; times <= 3; times++)
            for (int i = 1; i <= 49; i++)
            {
                if (dp[i] == 0)
                {
                    w[times] = i;
                    dp[i] = 1;
                    break;
                }
            }
        for (int times = 7; times >= 4; times--)
        {
            for (int i = 49; i >= 1; i--)
            {
                if (dp[i] == 0)
                {
                    w[times] = i;
                    dp[i] = 1;
                    break;
                }
            }
        }
        ans[week] = w[4];
    }
    sort(ans, ans + 7);
    cout << ans[3]; //34
    return 0;
}
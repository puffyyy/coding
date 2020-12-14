#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <cstdlib>
#include <algorithm>
using namespace std;
const int MS = 1e5 + 5;
#define mod 1000000007
int d_13[7] = {1, 10, 9, 12, 3, 4};
int dp[2][16];
char ch[MS];
int main()
{
    scanf("%s", ch);
    int len = strlen(ch);
    if (ch[len - 1] != '?')
        dp[0][ch[len - 1] - '0'] = 1;
    else
        for (int i = 0; i <= 9; i++)
            dp[0][i] = 1;
    int now = 1, pre = 0;
    for (int i = len - 2; i >= 0; i--)
    {
        int pos = len - 1 - i;
        memset(dp[now], 0, sizeof(int) * 16);
        if (ch[i] == '?')
        {
            for (int j = 0; j <= 12; j++)
            {
                for (int k = 0; k <= 9; k++)
                {
                    int p = (k * d_13[pos % 6] + j) % 13;
                    dp[now][p] += dp[pre][j];
                    dp[now][p] -= (dp[now][p] > mod ? mod : 0);
                }
            }
        }
        else
        {
            int cur = (ch[i] - '0') * d_13[pos % 6];
            for (int j = 0; j <= 12; j++)
            {
                int p = (cur + j) % 13;
                dp[now][p] += dp[pre][j];
                dp[now][p] -= (dp[now][p] > mod ? mod : 0);
            }
        }
        swap(now, pre);
    }
    printf("%d", dp[pre][5]);
    return 0;
}
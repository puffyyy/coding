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
const int mod = 1e9 + 7;
int dp[MS][13];
char str[MS];
int d_13[7] = {1, 10, 9, 12, 3, 4};
int main()
{
    scanf("%s", str + 1);
    int len = strlen(str + 1);
    int tmp;
    int pow_10 = 0;
    if (str[len] != '?')
    {
        tmp = str[len] - '0';
        dp[len][tmp] = 1;
    }
    else
    {
        for (int i = 0; i <= 9; i++)
            dp[len][i] = 1;
    }
    for (int i = len - 1; i >= 1; i--)
    {
        pow_10 = len - i;
        if (str[i] != '?')
        {
            tmp = d_13[pow_10 % 6] * (str[i] - '0');
            for (int j = 0; j <= 12; j++)
            {
                dp[i][(tmp + j) % 13] += dp[i + 1][j];
                dp[i][(tmp + j) % 13] %= mod;
            }
        }
        else
        {
            for (int k = 0; k <= 9; k++)
            {
                tmp = d_13[pow_10 % 6] * k;
                for (int j = 0; j <= 12; j++)
                {
                    dp[i][(tmp + j) % 13] += dp[i + 1][j];
                    dp[i][(tmp + j) % 13] %= mod;
                }
            }
        }
    }
    printf("%d", dp[1][5]);
    return 0;
}
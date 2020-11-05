#include <cstdio>
using namespace std;
typedef long long ll;
ll dp[20][20][20][2][2][2][2][2];
ll A[20], B[20], res = 0;
int main()
{
    ll a, b;
    scanf("%lld%lld", &a, &b);
    for (int i = 11; i >= 1; i--)
    {
        A[i] = a % 10;
        B[i] = b % 10;
        a /= 10;
        b /= 10;
    }
    //位置 数 当前的数与前面的数有几个相同 有无连续的3个 有4 有8 达到边界 达到边界
    for (int j = A[1]; j <= B[1]; j++)
        dp[1][j][1][0][j == 4 ? 1 : 0][j == 8 ? 1 : 0][j == A[1] ? 1 : 0][j == B[1] ? 1 : 0] = 1;
    for (int i = 1; i <= 10; i++)
        for (int j = 0; j <= 9; j++)
            for (int k = 1; k <= 11; k++)
                for (int p = 0; p <= 1; p++)
                    for (int a = 0; a <= 1; a++)
                        for (int b = 0; b <= 1; b++)
                            for (int c = 0; c <= 1; c++)
                                for (int d = 0; d <= 1; d++)
                                    if (dp[i][j][k][p][a][b][c][d]) //如果这种情况没错，则考虑在此基础上进行下一位操作
                                    {
                                        int l = 0, r = 9;
                                        if (c && d)
                                        {
                                            l = A[i + 1];
                                            r = B[i + 1];
                                        }
                                        else if (c && !d)
                                            l = A[i + 1];
                                        else if (!c && d)
                                            r = B[i + 1];
                                        for (int t = l; t <= r; t++)
                                        {
                                            int x = (t == j) ? k + 1 : 1;
                                            dp[i + 1][t][x][p | (x >= 3 ? 1 : 0)][a | (t == 4 ? 1 : 0)][b | (t == 8 ? 1 : 0)]
                                              [c & (t == A[i + 1] ? 1 : 0)][d & (t == B[i + 1] ? 1 : 0)] += dp[i][j][k][p][a][b][c][d];
                                        }
                                    }
    for (int j = 0; j <= 9; j++)
        for (int k = 1; k <= 12; k++)
            for (int c = 0; c <= 1; c++)
                for (int d = 0; d <= 1; d++)
                    res += dp[11][j][k][1][0][0][c][d] + dp[11][j][k][1][0][1][c][d] + dp[11][j][k][1][1][0][c][d];
    printf("%lld\n", res);
    return 0;
}
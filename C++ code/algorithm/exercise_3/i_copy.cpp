#include <iostream>
#include <cstdio>
#define ll long long
#define maxn 100001
#define MOD 1000000007
using namespace std;

int a[maxn], b[maxn], c[maxn];
ll dp[maxn][2][2];
int n;

void recur(int i)
{
    if (a[i])
        recur(a[i]);
    if (b[i])
        recur(b[i]);
    for (int v1 = 0; v1 < 2; v1++) //v1 v3正确 v2 v4错误
    {
        for (int v2 = 0; v2 < 2; v2++)
        {
            for (int v3 = 0; v3 < 2; v3++)
            {
                for (int v4 = 0; v4 < 2; v4++)
                {
                    int j = !(v1 & v3); // i 的正确输出
                    int k = !(v2 & v4); // i 的可能错误输出
                    if (c[i] != -1)     //change
                        k = c[i];

                    dp[i][j][k] += dp[a[i]][v1][v2] * dp[b[i]][v3][v4]; //dp公式
                    dp[i][j][k] %= MOD;
                }
            }
        }
    }
}

int main()
{
    while (~scanf("%d", &n))
    {
        for (int i = 1; i <= n; i++)
            scanf("%d%d%d", a + i, b + i, c + i);
        dp[0][0][0] = dp[0][1][1] = 1; //[0][][]表示输入 输入一定正确 初始化为1个
        recur(1);                      //dp[i][j][k],三个维度分别代表着：当前节点编号，理论输出值，实际输出值。
        printf("%d\n", (dp[1][0][1] + dp[1][1][0]) % MOD);
    }
    return 0;
}
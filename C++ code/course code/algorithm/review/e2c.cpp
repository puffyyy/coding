#include <cstdio>
using namespace std;
const int MS = 1e7 + 5;
int dp[MS];

int main()
{
    int n;
    scanf("%d", &n);
    int cnt = 1, j = 0;
    for (int i = 1; i <= n; ++i, ++j)
    {
        if (j == cnt)
        {
            j = 0;
            cnt *= 2;
            dp[i] = 1;
        }
        else
            dp[i] = 1 + dp[i - cnt];
        printf("%d ", dp[i]);
    }
    return 0;
}
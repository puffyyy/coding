#include <cstdio>
#include <cstring>
using namespace std;
int a;
bool dp[1001];
int main()
{
    int t, n;
    scanf("%d", &t);
    while (t--)
    {
        scanf("%d", &n);
        memset(dp, 0, sizeof(dp));
        dp[0] = 1;
        for (int i = 1; i <= n; i++)
        {
            scanf("%d", &a);
            for (int j = 1000; j >= a; j--)
                dp[j] = dp[j] | dp[j - a];
        }
        int cnt = 0;
        for (int j = 1; j <= 1000; j++)
            cnt += dp[j];

        printf("%d\n", cnt);
    }
    return 0;
}
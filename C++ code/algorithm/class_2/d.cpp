#include <cstdio>
#include <cstring>
using namespace std;
int a[55];
bool dp[1001];
int main()
{
    int t, n;
    scanf("%d", &t);
    while (t--)
    {
        scanf("%d", &n);
        for (int i = 1; i <= n; i++)
            scanf("%d", a + i);
        memset(dp, 0, sizeof(dp));
        dp[0] = 1;
        for (int i = 1; i <= n; i++)
        {
            for (int j = 1000; j >= a[i]; j--)
                dp[j] = dp[j] | dp[j - a[i]];
        }
        int cnt = 0;
        for (int j = 1; j <= 1000; j++)
            if (dp[j])
                cnt++;

        printf("%d\n", cnt);
    }
    return 0;
}
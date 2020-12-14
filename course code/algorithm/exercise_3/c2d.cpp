#include <cstdio>
#include <cstring>
#include <cstdlib>
using namespace std;
const int MS = 1e3 + 5;
bool dp[MS];
int a[MS];
int main()
{
    int t;
    scanf("%d", &t);
    while (t--)
    {
        memset(dp, 0, sizeof(dp));
        int n;
        scanf("%d", &n);
        for (int i = 0; i < n; i++)
            scanf("%d", a + i);
        dp[0] = 1;
        for (int i = 0; i < n; i++)
            for (int j = 1000; j >= a[i]; j--)
            {
                dp[j] |= dp[j - a[i]];
            }
        int cnt = 0;
        for (int j = 1000; j > 0; j--)
        {
            cnt = cnt + dp[j];
        }
        printf("%d\n", cnt);
    }
    return 0;
}
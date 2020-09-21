#include <cstdio>
using namespace std;
const int Size = 1000006;
int tmp, sum[Size];
int main()
{
    int n, q, l, r;
    while (~scanf("%d%d", &n, &q))
    {
        int ans = 0;
        for (int i = 1; i <= n; ++i)
        {
            scanf("%d", &tmp);
            sum[i] = (sum[i - 1] + (tmp % 10007)) % 10007;
        }
        for (int i = 0; i < q; ++i)
        {
            scanf("%d%d", &l, &r);
            ans = (sum[r] - sum[l - 1] + 10007) % 10007;
            printf("%d\n", ans);
        }
    }
    return 0;
}
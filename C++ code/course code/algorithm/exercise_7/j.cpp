#include <cstdio>
#include <cstring>
#include <cstdlib>
using namespace std;
typedef long long ll;
const int MS = 1e6;
short vis[MS];
int t, n, a, b, c, d, e;
void dfs(int x)
{
    if (vis[(x + n) % n] == 2)
        return;
    ++vis[(x + n) % n];
    dfs(((((1LL * a * x % n + b) * x % n + c) * x % n + d) * x % n + e) % n);
}
int main()
{

    scanf("%d", &t);
    while (t--)
    {
        memset(vis, 0, sizeof(short) * MS);
        int ans = 0;
        scanf("%d%d%d%d%d%d", &n, &a, &b, &c, &d, &e);
        dfs(0);
        for (int i = 0; i < n; i++)
        {
            if (vis[i] == 2)
                ++ans;
        }
        printf("%d\n", ans);
    }

    return 0;
}
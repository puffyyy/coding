#include <cstdio>
#include <cstring>
#include <cmath>
#include <cstdlib>
#include <algorithm>
using namespace std;
typedef long long int ll;
int n, x, y;
ll a[1000006], cnt;
bool check(int tmp)
{
    return tmp >= x && tmp <= y;
}
int main()
{
    //ios::sync_with_stdio(false);
    scanf("%d%d%d", &n, &x, &y);
    if (x > y)
        swap(x, y);
    int tmp;
    for (int i = 1; i <= n; ++i)
    {
        scanf("%d", &tmp);
        a[i] = a[i - 1] + tmp;
    }
    register int i, j;
    for (i = 0; i <= n - 1; ++i)
    {
        for (j = i + 1; j <= n; ++j)
        {
            if (check(a[j] - a[i]))
                ++cnt;
        }
    }
    printf("%lld", cnt);
    return 0;
}
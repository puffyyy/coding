#include <cstdio>
using namespace std;
typedef long long ll;
const int MS = 1e2 + 5;
ll a[MS] = {1, 1};
ll fun(int n)
{
    if (n < 0)
        return 0;
    if (a[n])
        return a[n];
    a[n] = fun(n - 1) + fun(n - 2) + fun(n - 4) + fun(n - 5);
    return a[n];
}
int main()
{
    int n;
    while (~scanf("%d", &n))
    {
        printf("%lld\n", fun(n) + fun(n - 3));
    }
    return 0;
}
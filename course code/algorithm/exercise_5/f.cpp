#include <cstdio>
#include <algorithm>
using namespace std;
typedef long long ll;
#define maxn 1000005
ll n, a[maxn], sum, s[maxn], ans;
int main()
{
    scanf("%lld", &n);
    for (int i = 1; i <= n; i++)
    {
        scanf("%lld", &a[i]);
        sum += a[i];
    }
    sum /= n;
    for (int i = 1; i < n; i++)
    {
        a[i] -= sum;
        s[i + 1] = s[i] + a[i];
    }
    // sort(s + 1, s + n + 1);
    nth_element(s + 1, s + 1 + n / 2, s + n + 1);
    for (int i = 1; i <= n; i++)
    {
        ans += abs(s[n / 2 + 1] - s[i]);
    }
    printf("%lld", ans);
    return 0;
}
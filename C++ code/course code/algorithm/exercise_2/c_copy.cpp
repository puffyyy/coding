#include <iostream>
using namespace std;
int ans[10000005];

int main()
{
    ios::sync_with_stdio(false);
    int n;
    cin >> n;
    register int i;
    for (i = 1; i <= n; ++i)
    {
        ans[i] = ans[i & (i - 1)] + 1;
        cout << ans[i] << ' ';
    }
    // for (i = 1; i <= n; ++i)
    // {
    //     ans[i] = ans[i >> 1] + (i & 1);
    //     cout << ans[i] << ' ';
    // }
    return 0;
}
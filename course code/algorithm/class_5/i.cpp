#include <iostream>
#include <algorithm>
using namespace std;
typedef long long ll;
const int MS = 1e5 + 5;
ll nsum[MS], psum[MS];
ll ans;
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, k;
    cin >> n >> k;
    int temp;
    for (int i = 1; i <= n; i++)
    {
        cin >> temp;
        if (temp > 0)
            psum[i] = psum[i - 1] + temp, nsum[i] = nsum[i - 1];
        else
            nsum[i] = nsum[i - 1] + temp, psum[i] = psum[i - 1];
    }
    ll mi = -999999999999999999, ma = 999999999999999999;
    for (int i = 1; i <= n - k + 1; i++)
    {
        int j = i + k - 1;
        mi = mi > (nsum[j] - nsum[i - 1]) ? mi : (nsum[j] - nsum[i - 1]);
        ma = ma > (psum[j] - psum[i - 1]) ? (psum[j] - psum[i - 1]) : ma;
        // ans = max(ans, max(psum[n] + nsum[j] - nsum[i - 1], psum[n] - psum[j] + psum[i - 1]));
    }
    cout << max(psum[n] + mi, psum[n] - ma);
    return 0;
}
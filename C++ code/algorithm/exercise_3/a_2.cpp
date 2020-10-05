#include <iostream>
using namespace std;
typedef long long int ll;
int main()
{
    ios::sync_with_stdio(false);
    ll n;
    cin >> n;
    if (n < 6)
        cout << n;
    else
    {
        ll add;
        add = (n - 2) / 4;
        n = (n - 2) % 4;
        n += add * 9 + 2;
    }
    cout << n;
    return 0;
}
// 找规律
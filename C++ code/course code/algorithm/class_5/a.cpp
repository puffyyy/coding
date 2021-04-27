#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include <stack>
#include <queue>
#include <set>
using namespace std;
typedef long long ll;
const int MS = 1e5 + 5;

int main()
{
    //ios::sync_with_stdio(false);
    //cin.tie(nullptr);
    int t;
    cin >> t;
    ll a[3], b[3];
    while (t--)
    {
        for (int i = 0; i < 3; i++)
            cin >> a[i];
        for (int i = 0; i < 3; i++)
            cin >> b[i];
        cout << a[1] * b[2] - a[2] * b[1] << " " << -(a[0] * b[2] - a[2] * b[0]) << " " << a[0] * b[1] - a[1] * b[0] << endl;
    }
    return 0;
}
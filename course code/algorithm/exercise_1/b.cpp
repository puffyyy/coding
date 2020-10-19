#include <iostream>
#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include <stack>
#include <queue>

using namespace std;
bool judge(int a, int b, int c)
{
    if (a + b > c && a + c > b && b + c > a && abs(a - b) < c && abs(a - c) < b && abs(b - c) < a)
        return true;
    return false;
}
int main()
{
    int n;
    cin >> n;
    while (n--)
    {
        long long a, b, c;
        long long ans = 0;
        cin >> a >> b >> c;
        if (judge(a, b, c))
        {
            ans = (a + b + c) * (b + c - a) * (a + c - b) * (a + b - c);
            printf("%lld\n", ans);
        }
        else
        {
            cout << "momoga!" << endl;
        }
    }

    return 0;
}
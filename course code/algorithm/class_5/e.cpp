#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <cstdlib>
using namespace std;
typedef long long ll;
int main()
{
    ll t, x, y, vx, vy, n;
    cin >> t;
    while (t--)
    {
        bool flag = 1;
        cin >> n;
        cin >> x >> y >> vx >> vy;
        ll a, b, c, d;
        while (n--)
        {
            cin >> a >> b >> c >> d;
            if (flag)
            {
                flag = ((a - x) * (d - vy) == (b - y) * (c - vx) && (a - x) * (c - vx) + (d - vy) * (b - y) < 0) ? 0 : 1;
                if (c == vx && d == vy)
                    flag = 1;
                if (a == x && b == y)
                    flag = 0;
            }
        }
        if (flag == 0)
            printf("Dead\n");
        else
            printf("Alive\n");
    }
    return 0;
}
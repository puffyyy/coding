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
int gcd(int a, int b)
{
    if (a < b)
        swap(a, b);
    if (b == 0)
        return a;
    return gcd(b, a % b);
}
// x*a+y*b=gcd(a,b)
void ex_gcd(int a, int b, int &x, int &y)
{
    if (b == 0)
    {
        x = 1, y = 0;
        return;
    }
    int xx, yy;
    ex_gcd(b, a % b, xx, yy);
    x = yy;
    y = xx - (a / b) * yy;
}
int main()
{
    //ios::sync_with_stdio(false);
    //cin.tie(nullptr);
    int cnt = 0;
    for (int i = 1; i <= 2020; i++)
        for (int j = 1; j <= 2020; j++)
        {
            if (gcd(i, j) == 1)
                cnt += 1;
        }
    printf("%d", cnt);
    return 0;
}
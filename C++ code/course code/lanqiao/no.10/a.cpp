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
int sp[4] = {2, 0, 1, 9};
bool contain(int x)
{
    int re;
    while (x)
    {
        re = x % 10;
        for (int i : sp)
        {
            if (i == re)
                return true;
        }
        x /= 10;
    }
    return false;
}

int main()
{
    //ios::sync_with_stdio(false);
    //cin.tie(nullptr);
    long long ans = 0;
    for (int i = 1; i <= 2019; i++)
    {
        if (contain(i))
            ans += i * i;
    }
    cout << ans;
    return 0;
}
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
typedef long long int ll;
ll n, energy, ans;

int main()
{
    cin >> n;
    for (int i = 0; i < n; ++i)
    {
        if (energy == 100)
        {
            energy -= 50;
            ans += 6;
        }
        else
        {
            energy += 20;
            if (energy > 100)
                energy = 100;
            ans += 1;
        }
    }
    printf("%lld\n", ans);
    return 0;
}
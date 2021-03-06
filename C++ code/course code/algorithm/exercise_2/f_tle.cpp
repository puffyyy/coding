#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <cstdlib>
#include <algorithm>
using namespace std;
const int MS = 100000004;
int high[MS];
int main()
{
    int max_, t;
    scanf("%d", &t);

    while (t--)
    {
        int m, k, a, b;
        scanf("%d%d%d%d", &m, &k, &a, &b);
        int l, r;
        max_ = m;
        high[m] = 1;
        while (k--)
        {
            --high[max_];
            l = int(1.0 * a / b * max_);
            r = max_ - l;
            ++high[l];
            ++high[r];
            while (!high[max_])
                --max_;
        }

        printf("%d\n", max_);
        memset(high, 0, sizeof(int) * (max_ + 2));
    }
    return 0;
}
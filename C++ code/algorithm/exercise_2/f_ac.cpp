#include <iostream>
#include <cstdio>
#include <queue>
#include <cstdlib>
using namespace std;

int main()
{
    int t, maxi;
    scanf("%d", &t);
    while (t--)
    {
        queue<int> high, low;
        int m, k, a, b;
        scanf("%d%d%d%d", &m, &k, &a, &b);
        int l, r;
        high.push(m);
        while (k--)
        {
            if (low.empty() || high.front() >= low.front())
            {
                maxi = high.front();
                high.pop();
            }
            else
            {
                maxi = low.front();
                low.pop();
            }
            l = int(1.0 * a / b * maxi);
            r = maxi - l;
            if (l > r)
            {
                high.push(l);
                low.push(r);
            }
            else
            {
                high.push(r);
                low.push(l);
            }
        }
        printf("%d\n", high.front() > low.front() ? high.front() : low.front());
    }
    return 0;
}
#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <math.h>
using namespace std;
int n, m;

int fun(int n)
{
    if (n == 0)
        return m;
    return fun(n - 1) * 3 / 2;
}
int main()
{
    int t;
    cin >> t;
    while (t--)
    {
        cin >> n >> m;
        if (m == 0)
        {
            printf("0\n");
            continue;
        }
        else if (n == 0 || m == 1)
        {
            printf("%d\n", m);
            continue;
        }
        printf("%d\n", fun(n));
    }

    return 0;
}
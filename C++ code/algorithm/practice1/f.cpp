#include <iostream>
#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include <stack>
#include <queue>

using namespace std;
int n;
int main()
{
    while (~scanf("%d", &n))
    {
        int tmp;
        int cnt = 0;
        for (int i = 0; i < n; ++i)
        {
            scanf("%d", &tmp);
            while (tmp && tmp % 2 == 0)
            {
                cnt++;
                tmp /= 2;
            }
        }
        printf("%d\n", cnt);
    }
    return 0;
}
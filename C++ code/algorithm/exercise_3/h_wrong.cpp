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
int a[2500], b[2500];
int main()
{
    //ios::sync_with_stdio(false);
    int t, k;
    scanf("%d", &t);
    while (t--)
    {
        int flag = 1;
        scanf("%d", &k);
        for (int i = 0, size = 1, pos = 1; i <= k; ++i)
        {
            size <<= 1;
            for (; pos < size; ++pos)
                scanf("%d", &a[pos]);
        }
        for (int i = 0, size = 1, pos = 1; i <= k; ++i)
        {
            size <<= 1;
            for (; pos < size; ++pos)
                scanf("%d", &b[pos]);
        }
        if (a[1] == b[1])
            for (int i = 0, size = 1, pos = 1; i < k; ++i)
            {
                size <<= 1;
                for (; pos < size; ++pos)
                {
                    if ((a[(pos << 1)] == b[(pos << 1)] && a[(pos << 1) + 1] == b[(pos << 1) + 1]) || a[(pos << 1)] == b[(pos << 1) + 1] && a[(pos << 1) + 1] == b[(pos << 1)])
                        continue;
                    else
                        flag = 0;
                }
            }
        else
            flag = 0;

        if (flag)
            printf("Yes\n");
        else
            printf("No\n");
    }

    return 0;
}
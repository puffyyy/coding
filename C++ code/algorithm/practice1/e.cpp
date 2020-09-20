#include <iostream>
#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include <stack>
#include <queue>

using namespace std;
int main()
{
    int cnt = 0, n;
    long long ch = 0, pre = -1;
    cin >> n;
    while (n--)
    {
        scanf("%lld", &ch);
        if (-1 == pre)
        {
            cnt++;
            pre = ch;
            continue;
        }
        if (pre == ch)
            cnt++;
        else
        {
            if (cnt == 0)
            {
                pre = ch;
                cnt = 1;
            }
            else
                cnt--;
        }
    }
    printf("%lld", pre);

    return 0;
}
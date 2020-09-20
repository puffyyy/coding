#include <iostream>
#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <vector>
#include <stack>
#include <queue>

using namespace std;
char s[1000006];
int main()
{
    long long ans = 0;
    scanf("%s", s);
    for (int i = 0; i < strlen(s); i++)
    {
        if (s[i] == 'X')
            continue;
        if (s[i] == 'Y')
            ans += 2;
        else if (s[i] == 'Z')
        {
            long long cnt = 0;
            while (s[i] == 'Z')
            {
                cnt++;
                i++;
            }
            i--;
            ans += (cnt + 1) * cnt / 2;
        }
    }
    printf("%lld", ans);
    return 0;
}
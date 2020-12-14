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
int a;
int main()
{
    int n;
    scanf("%d", &n);
    int cnt = 0, flag = 1;
    for (int i = 1; i <= n; i++)
    {
        scanf("%d", &a);
        if (flag)
            if (a == i)
            {
                ++cnt;
                flag = 0;
                continue;
            }
        flag = 1;
    }
    printf("%d", cnt);
    return 0;
}
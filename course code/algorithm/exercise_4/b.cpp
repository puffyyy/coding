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
const int MS = 1e6 + 5;
int a[MS];
int main()
{
    //ios::sync_with_stdio(false);
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
    {
        scanf("%d", a + i);
    }
    int q;
    scanf("%d", &q);
    int que;
    for (int i = 0; i < q; i++)
    {
        scanf("%d", &que);
        int pos = lower_bound(a, a + n, que) - a;
        if (a[pos] == que)
            printf("Yes %d\n", pos + 1);
        else
            printf("No\n");
    }
    return 0;
}
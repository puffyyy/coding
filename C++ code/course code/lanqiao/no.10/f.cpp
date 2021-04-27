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
const int MS = 2e6 + 5;
int tree[MS];
int n;
int main()
{

    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
    {
        scanf("%d", tree + i);
    }
    int ans = 1;
    int all_vis_id = 1;
    ll maxans = tree[1];
    int deepth = 1;
    int curDeepthOfNum = 1;
    while (all_vis_id <= n)
    {
        curDeepthOfNum <<= 1;
        deepth++;
        ll t_max = 0;
        for (int i = 1; i <= curDeepthOfNum; i++)
        {
            t_max += tree[i + all_vis_id];
        }
        if (t_max > maxans)
        {
            maxans = t_max;
            ans = deepth;
        }
        all_vis_id += curDeepthOfNum;
    }
    printf("%d", ans);
    return 0;
}
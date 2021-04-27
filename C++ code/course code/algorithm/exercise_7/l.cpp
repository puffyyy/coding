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
const int MAXVER = 5e6 + 5;
int parent[MAXVER];
int n, k, l, r;
void initUF()
{
    for (int i = 0; i < n + 4; i++)
        parent[i] = -1;
}
int findUF(int x)
{
    int s, tmp;
    for (s = x; parent[s] >= 0 && s != parent[s]; s = parent[s])
        ;
    return s;
}
int main()
{
    while (~scanf("%d%d", &n, &k))
    {
        int ans = n, terminal = n + 1, i;
        initUF();
        while (k--)
        {
            scanf("%d%d", &l, &r);
            for (i = l; i <= r; i++)
            {
                if (parent[i] < 0)
                {
                    parent[i] = findUF(r);
                    --ans;
                }
                else
                    i = findUF(i);
            }
            printf("%d\n", ans);
        }
    }
    return 0;
}
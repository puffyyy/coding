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
const int MS = 1e6 + 5;
int rt[MS];
int n;
int read[MS];

int find(int x)
{
    int s = x;
    for (; rt[s] >= 0; s = rt[s])
        ;
    int tmp;
    while (x != s)
    {
        tmp = rt[x];
        rt[x] = s;
        x = tmp;
    }
}
void merge(int l, int r)
{
    rt[l] = r;
}
int main()
{
    cin >> n;
    rt[0] = -1;
    for (int i = 1; i <= n; i++)
    {
        rt[i] = -1;
        cin >> read[i];
    }
    int now;
    int root;
    for (int i = 1; i <= n; i++)
    {
        now = read[i];
        root = find(now);
        if (root == -1)
        {
            merge(now, now + 1);
            continue;
        }
        else
        {
            read[i] = root;
            merge(root, root + 1);
            // merge(now, root + 1);
        }
    }
    for (int i = 1; i <= n; i++)
        printf("%d ", read[i]);
    return 0;
}
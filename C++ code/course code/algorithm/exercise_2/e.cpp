#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <cstdlib>
#include <algorithm>
using namespace std;
typedef long long int ll;

int n, m;
int tree[10005];
int maxm[10005];

int main()
{
    int tmp;
    cin >> n >> m;

    for (int i = 1; i <= n; ++i)
    {
        cin >> tmp;
        tree[i] = tree[i - 1] + tmp;
    }
    int max_i = tree[n];
    maxm[n] = max_i;
    for (int i = n - 1; i >= 1; --i)
    {
        for (int j = n; j - i >= 0; --j)
        {
            max_i = max(max_i, tree[j] - tree[j - i]);
        }
        maxm[i] = (maxm[i + 1], max_i);
    }
    for (int i = 1; i <= m; ++i)
    {
        scanf("%d", &tmp);
        printf("%d\n", maxm[tmp]);
    }
    return 0;
}

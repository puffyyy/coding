#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <cstdlib>
#include <algorithm>
using namespace std;
typedef long long int ll;

int n, m;
int tree[10005]; //树状数组
int maxm[10005];

int main()
{
    ios::sync_with_stdio(false);
    int tmp;
    cin >> n >> m;

    for (int i = 1; i <= n; ++i)
    {
        cin >> tmp;
    }
    for (int i = 1; i <= m; ++i)
    {
        cin >> tmp;
        if (maxm[tmp] != 0)
            cout << maxm[tmp];
        else
        {
        }
    }

    return 0;
}

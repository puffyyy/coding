#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <cstdlib>
#include <algorithm>
#include <stack>
using namespace std;
const int MS = 1e3 + 5;
int a[MS][MS];
int upflow[MS];
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin >> t;
    int n, m;
    while (t--)
    {
        int ans = 0;
        int tmp;
        cin >> n >> m;
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= m; j++)
                cin >> a[i][j];
        memset(upflow, 0, sizeof(upflow));
        for (int i = 1; i <= n; i++)
        {
            stack<int> s;
            s.push(0);
            upflow[0] = 0x7fffffff;
            for (int j = 1; j <= m; j++)
            {
                tmp = a[i][j];
                if (tmp > upflow[j])
                {
                    tmp -= upflow[j];
                    while (upflow[s.top()] < tmp)
                        tmp -= upflow[s.top()],
                            upflow[s.top()] = 0, s.pop();
                    upflow[s.top()] -= tmp;
                    upflow[j] = a[i][j];
                }
                s.push(j);
            }
            ans += 0x7fffffff - upflow[0];
        }
        cout << ans << endl;
    }
    return 0;
}
/*
1
3 3
0 5 1
5 11 5 
1 5 0 
7187498

*/

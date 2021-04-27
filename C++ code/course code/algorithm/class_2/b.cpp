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
const int MS = 1e5 + 5;
int a;
int main()
{
    int n, k;
    ios::sync_with_stdio(false);
    while (cin >> n >> k)
    {
        ll ans = 0;
        priority_queue<int, vector<int>, less<int>> que;
        for (int i = 0; i < n; i++)
        {
            cin >> a;
            que.push(a);
        }
        while (k--)
        {
            int tmp = que.top() >> 1;
            que.pop();
            que.push(tmp);
        }
        while (!que.empty())
        {
            ans += que.top(), que.pop();
        }
        cout << ans << endl;
    }

    return 0;
}
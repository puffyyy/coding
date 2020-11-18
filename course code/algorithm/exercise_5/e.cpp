#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <queue>
using namespace std;
typedef long long ll;
const int MS = 1e5 + 5;

int main()
{
    //ios::sync_with_stdio(false);
    //cin.tie(nullptr);
    int n;
    while (scanf("%d", &n) != EOF)
    {
        priority_queue<int, vector<int>, greater<int>> que;
        int tmp;
        ll ans = 0;
        for (int i = 0; i < n; i++)
        {
            scanf("%d", &tmp);
            que.push(tmp);
        }
        while (que.size() > 3)
        {
            tmp = que.top(), que.pop();
            tmp += que.top(), que.pop();
            tmp += que.top(), que.pop();
            que.push(tmp);
            ans += tmp;
        }
        if (que.size() == 3)
        {
            tmp = que.top(), que.pop();
            tmp += que.top(), que.pop();
            ans += tmp;
        }
        printf("%lld\n", ans);
    }
    return 0;
}
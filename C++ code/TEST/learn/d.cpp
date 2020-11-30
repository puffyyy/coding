#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <cstdlib>
#include <algorithm>
using namespace std;
typedef long long ll;
const int MS = 1e5 + 5;
ll n, mytime, st, wt;
ll a[MS];
bool cmp(ll a, ll b)
{
    if (a > st && b > st)
    {
        return a > b;
    }
    else if (a > st)
    {
        return 0;
    }
    else if (b > st)
    {
        return 1;
    }
    else
    {
        return a < b;
    }
}
ll allwt;
int cnt;
int main()
{
    //ios::sync_with_stdio(false);
    //cin.tie(nullptr);
    cin >> n >> mytime >> st >> wt; //solve mytime wrong mytime
    for (int i = 1; i <= n; i++)
    {
        cin >> a[i];
    }
    stable_sort(a + 1, a + n + 1, cmp);
    ll alltime = 0;
    int flag = 1;
    for (cnt = 1; cnt <= n; cnt++)
    {
        alltime += st + (a[cnt] >= st ? st : a[cnt]);
        allwt += alltime + (a[cnt] >= st ? 0 : wt);
        if (alltime > mytime)
        {
            flag = 0;
            break;
        }
    }
    if (!flag)
    {
        allwt = allwt - alltime - (a[cnt] >= st ? 0 : wt);
        alltime -= (st + (a[cnt] >= st ? st : a[cnt]));
    }
    cnt--;
    int pos;
    for (pos = cnt; pos >= 0; pos--)
        if (a[pos] < st)
            break;
    mytime -= alltime;
    for (; pos >= 1; pos--)
    {
        if (st - a[pos] <= mytime)
        {
            mytime -= st - a[pos];
            allwt = allwt - (a[pos] - st) * (1 + cnt - pos) - wt;
        }
    }
    cout << cnt << " " << allwt;
    return 0;
}
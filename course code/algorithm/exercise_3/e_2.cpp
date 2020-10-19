#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <vector>
using namespace std;
const int MS = 1e6 + 5;
int n, x, y;
int tree[MS], sum[MS], high[MS], low[MS], cnt;
vector<int> temp;

void plusone(int i)
{
    while (i <= n + 3)
    {
        ++tree[i];
        i += (i & (-i));
    }
}
int getcnt(int i)
{
    int ret = 0;
    while (i > 0)
    {
        ret += tree[i];
        i -= (i & (-i));
    }
    return ret;
}
int main()
{
    //ios::sync_with_stdio(false);
    register int i;
    scanf("%d%d%d", &n, &x, &y);
    if (x > y)
        swap(x, y);
    int tmp;
    for (i = 1; i <= n; ++i)
    {
        scanf("%d", &tmp);
        sum[i] = sum[i - 1] + tmp;
        high[i] = sum[i] - x, low[i] = sum[i] - y;
    }
    for (i = 0; i < n; ++i)
        temp.push_back(sum[i]);
    sort(temp.begin(), temp.end()); //nlogn
    temp.resize(unique(temp.begin(), temp.end()) - temp.begin());

    for (i = 0; i <= n; ++i) //3nlogn
    {
        sum[i] = lower_bound(temp.begin(), temp.end(), sum[i]) - temp.begin() + 2;
        low[i] = lower_bound(temp.begin(), temp.end(), low[i]) - temp.begin() + 2;
        high[i] = upper_bound(temp.begin(), temp.end(), high[i]) - temp.begin() + 2;
    }
    plusone(sum[0]);
    for (i = 1; i <= n; ++i) //3nlogn
    {
        cnt += getcnt(high[i] - 1) - getcnt(low[i] - 1);
        plusone(sum[i]);
    }
    printf("%d", cnt);
    return 0;
}
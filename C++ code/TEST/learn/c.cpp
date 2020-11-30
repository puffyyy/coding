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
#define MOD 998244353
const int MS = 1e5 + 5;
char str[MS];
ll pow6mod[MS] = {6};
ll c0[10] = {1, 4, 6, 24, 36, 144, 216, 864, 1296, 5184};
void pred()
{
    ll temp = pow6mod[0];
    for (int i = 1; i < MS; i++)
    {
        for (int j = 1; j < 10; j++)
            temp = temp * pow6mod[i - 1] % MOD; //quick pow
        pow6mod[i] = temp;
    }
}
ll cal(int x, int bit)
{
    if (bit == 0)
        return c0[x];
    ll ret = 1;
    if (x & 1 == 0)
    {
        int i = x / 2;
        for (; i > 0; i--)
        {
            ret = ret * pow6mod[bit] % MOD;
        }
        return ret;
    }
    else
    {
        int i = x * 10 / 2;
        int i10 = i / 10;
        for (; i10 > 0; i10--)
        {
            ret = ret * pow6mod[bit] % MOD;
        }
        i = i % 10;
        bit--;
        for (; i > 0; i--)
        {
            ret = ret * pow6mod[bit] % MOD;
        }
        return ret;
    }
}
int main()
{
    cin >> str;
    int len = strlen(str);
    pred();
    ll ans = 1;
    for (int i = len - 1; i >= 0; i--)
    {
        ans = ans * cal(str[i] - '0', len - 1 - i) % MOD;
    }
    cout << ans;
    return 0;
}
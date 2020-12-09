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
typedef unsigned long long ull;
#define Cardinal 10
const int MS = 1e2 + 5;
//hash[i]=(hash[i−1])∗p+idx(s[i])%mod;
//若已知一个|S|=n的字符串的hash值，hash[i],1≤i≤n，其子串sl..sr,1≤l≤r≤n，对应的hash值为：
//hash(l~r)=((hash[r]−hash[l−1]∗p^(r−l+1))%mod+mod)%mod
ull p[MS] = {1};
ull H[MS];
string a, b;
ull pre(string &b)
{
    ull ret = b[0] - 'a';
    for (int i = 1; i < b.size(); i++)
        ret = ret * Cardinal + b[i] - 'a';
    return ret;
}
int main()
{
    //ios::sync_with_stdio(false);
    //cin.tie(nullptr);
    cin >> a >> b;
    queue<int> que;
    ull hash_a;
    ull hash_b = pre(b);
    cout << hash_b << endl;
    int lena = a.size(), lenb = b.size();
    for (int i = 0; i <= lena - lenb; i++)
    {
        int j = i + lenb - 1;
        hash_a = 0;
        for (int k = i; k <= j; k++)
        {
            hash_a = hash_a * Cardinal + a[k] - 'a';
        }
        cout << hash_a << " ";
        if (hash_a == hash_b)
        {
            que.push(i);
        }
    }
    cout << endl;
    if (que.size())
        while (que.size())
        {
            cout << que.front() << " ";
            que.pop();
        }
    else
        cout << endl;
    return 0;
}
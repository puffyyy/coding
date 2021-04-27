#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include <set>
using namespace std;
typedef long long int ll;
char bracket[] = "([{}])"; // 0-5
string brackets[3] = {"()", "[]", "{}"};
vector<vector<set<string>>> dp(3);
void makebrackets(int n, int type)
{
    if (!dp[type][n].empty())
        return;
    if (dp[type][0].empty())
        dp[type][0].insert("");
    if (dp[type][1].empty())
        for (int i = 0; i < type + 1; ++i)
            dp[type][1].insert(brackets[i]);

    for (int i = 2; i <= n; i++)
    {
        if (!dp[type][i].empty())
            continue;
        for (int j = 0; j < i; j++)
        {
            for (string p : dp[type][j])
                for (string q : dp[type][i - j - 1])
                {
                    for (int k = 0; k < type + 1; ++k)
                    {
                        string str = bracket[k] + p + bracket[5 - k] + q;
                        dp[type][i].insert(str);
                    }
                }
        }
    }
}
namespace io
{
    const int SIZE = 1 << 22 | 1;
    char iBuf[SIZE], *iS, *iT, c;
    char oBuf[SIZE], *oS = oBuf, *oT = oBuf + SIZE;
    inline void flush()
    {
        fwrite(oBuf, 1, oS - oBuf, stdout);
        oS = oBuf;
    }
    inline void putc(char x)
    {
        *oS++ = x;
        if (oS == oT)
            flush();
    }
    void print(string str)
    {
        const char *pos = str.c_str();
        while (*pos != '\0')
        {
            putc(*pos);
            ++pos;
        }
    }
    struct flusher
    {
        ~flusher() { flush(); }
    } _;
} // namespace io

using io ::print;
using io ::putc;
int main()
{
    int t;
    cin >> t;
    for (int i = 0; i < 3; i++)
        dp[i].resize(10);
    while (t--)
    {
        int n, k;
        cin >> n >> k;
        k -= 1;
        makebrackets(n, k);
        set<string>::iterator iter = dp[k][n].begin();
        while (iter != dp[k][n].end())
        {
            print(*iter);
            putc('\n');
            iter++;
        }
        putc('\n');
    }
    return 0;
}
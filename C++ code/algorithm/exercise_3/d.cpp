#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include <stack>
#include <queue>
#include <map>
using namespace std;
typedef long long int ll;
char list[] = "([{";
char rlist[] = ")]}";
map<char, int> mm;
stack<char> st;
void init()
{
    mm['('] = 1;
    mm[')'] = 2;
    mm['['] = 3;
    mm[']'] = 4;
    mm['{'] = 5;
    mm['}'] = 6;
}
void makebracket(int len, int k, string &bra)
{
    if (len == 0)
    {
        cout << bra << endl;
        return;
    }
    else
    {
        int i = 0;
        int flag = 0;
        for (; i < k; ++i)
        {
            if (len > st.size())
            {
                bra = bra + list[i];
                st.push(rlist[i]);
                makebracket(len - 1, k, bra);
                bra.erase(bra.length() - 1);
                st.pop();
            }
            if (!flag && !st.empty() && (len == st.size() || i + 1 >= k || mm[list[i + 1]] >= mm[st.top()]))
            {
                flag = 1;
                char tmp;
                bra = bra + st.top();
                tmp = (st.top());
                st.pop();
                makebracket(len - 1, k, bra);
                st.push(tmp);
                bra.erase(bra.length() - 1);
            }
        }
    }
}
int main()
{
    ios::sync_with_stdio(false);
    int t;
    cin >> t;
    init();
    while (t--)
    {
        int n, k;
        cin >> n >> k;
        string ans;

        makebracket(2 * n, k, ans);
        cout << endl;
    }
    return 0;
}
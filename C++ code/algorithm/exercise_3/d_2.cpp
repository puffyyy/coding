#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <cstdlib>
#include <algorithm>
#include <stack>
using namespace std;
typedef long long int ll;
char lc[] = {'(', '[', '{'};
char rc[] = {')', ']', '}'};
int cnt[3][2];
char str[20];
stack<char> st;
void makebrackets(int n, int type)
{
    int left = 0, right = 0;
    for (int i = 0; i < 3; i++)
        left += cnt[i][0], right += cnt[i][1];
    int cur = left + right;

    if (cur == (n << 1)) //n*2
    {
        for (int i = 0; i < (n << 1); ++i)
            putchar(str[i]);
        putchar('\n');
        return;
    }
    for (int i = 0; i < 3; ++i)
    {
        if (left < n && type > i)
        {
            str[cur] = lc[i];
            st.push(rc[i]);
            ++cnt[i][0];
            makebrackets(n, type);
            --cnt[i][0];
            st.pop();
        }
        if (cnt[i][1] < cnt[i][0] && st.top() == rc[i])
        {
            str[cur] = rc[i];
            st.pop();
            ++cnt[i][1];
            makebrackets(n, type);
            --cnt[i][1];
            st.push(rc[i]);
        }
    }
}
int main()
{
    int t;
    scanf("%d", &t);
    while (t--)
    {
        memset(cnt, 0, sizeof(cnt));
        int n, k;
        scanf("%d%d", &n, &k);
        makebrackets(n, k);
        putchar('\n');
    }
    return 0;
}
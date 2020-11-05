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
const int MS = 1e5 + 5;
string ans;
char sour[301];
char str[301];
int add[301][301];
int dp[301][301];
inline bool isbracket(char ch)
{
    return (ch == '(' || ch == ')' || ch == '[' || ch == ']' || ch == '{' || ch == '}' || ch == '<' || ch == '>');
}
inline bool match(char a, char b)
{
    if (a == '(' && b == ')')
        return true;
    if (a == '[' && b == ']')
        return true;
    if (a == '{' && b == '}')
        return true;
    if (a == '<' && b == '>')
        return true;
    return false;
}
inline string correspond(char ch)
{
    if (ch == '(' || ch == ')')
        return "()";
    if (ch == '[' || ch == ']')
        return "[]";
    if (ch == '{' || ch == '}')
        return "{}";
    if (ch == '<' || ch == '>')
        return "<>";
    return "";
}
void print_ans(int l, int r)
{
    if (l > r)
        return;
    if (l == r)
    {
        ans += correspond(str[l]);
    }
    else if (add[l][r] == -1)
    {
        if (dp[l][r - 1] < dp[l + 1][r])
        {
            print_ans(l, r - 1);
            print_ans(r, r);
        }
        else
        {
            print_ans(l, l);
            print_ans(l + 1, r);
        }
    }
    else if (add[l][r] == l)
    {
        ans += str[l];
        print_ans(l + 1, r - 1);
        ans += str[r];
    }
    else
    {
        print_ans(l, add[l][r] - 1);
        print_ans(add[l][r], r);
    }
}
int main()
{
    int rtop = -1; //最后一个字符的位置
    scanf("%s", sour);
    int len = strlen(sour);
    int top = 0;
    while (sour[top])
    {
        if (isbracket(sour[top]))
            str[++rtop] = sour[top];
        ++top;
    }
    int size = rtop + 1;
    for (int i = 0; i < size; ++i)
    {
        dp[i][i] = 1;
        for (int j = 0; j < size; ++j)
            add[i][j] = -1;
    }

    for (int l = 1; l < size; l++)
        for (int i = 0; i < size - l; i++)
        {
            int j = i + l;
            dp[i][j] = min(dp[i + 1][j], dp[i][j - 1]) + 1;
            for (int k = i; k < j; ++k)
                if (match(str[k], str[j]))
                    if (dp[i][k - 1] + dp[k + 1][j - 1] < dp[i][j])
                    {
                        dp[i][j] = dp[i][k - 1] + dp[k + 1][j - 1];
                        add[i][j] = k;
                    }
        }
    print_ans(0, size - 1);
    int anssize = ans.size();
    int i = 0, j = 0;
    for (; i < len && j < anssize;)
    {
        if (!isbracket(sour[i]))
            putchar(sour[i++]);
        else
        {
            while (ans[j] != sour[i])
            {
                putchar(ans[j++]);
            }
            putchar(sour[i++]);
            ++j;
        }
    }
    while (j < anssize)
        putchar(ans[j++]);
    while (i < len)
        putchar(sour[i++]);
    return 0;
}
//{([)}]{}{[}{)}

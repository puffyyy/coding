#include <iostream>
#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <vector>
#include <stack>
#include <queue>
using namespace std;

const int MAXSIZE = 1e5;
int n;

string deleteZero(string str) //除去前导0 后导0
{
    if (str[0] == '.') //case : .0000
        str.insert(0, "0");
    if (str[str.length() - 1] == '.') //case : 00000.
        str.erase(str.length() - 1);
    int i = 0, j = str.length() - 1;
    while (str[i] == '0')
        i++;
    if (str[i] == '.')
        i--;
    if (str.find('.') != string::npos)
    {
        while (str[j] == '0')
            j--;
        // if == '.'
    }
    if (j - i + 1 == 0)
        return "0";
    return str.substr(i, j - i + 1);
}
int split(string str, string &s_int, string &s_dot)
{
    int dot_pos = str.find('.');
    if (dot_pos == string::npos)
    {
        s_int = str.substr(0);
        s_dot = "";
    }
    else
    {
        s_int = str.substr(0, dot_pos);
        s_dot = str.substr(dot_pos + 1);
    }
    return dot_pos;
}

string solve(string str, int n)
{
    str = deleteZero(str);
    string s_int, s_dot;
    split(str, s_int, s_dot);                                           //返回 dot_pos  -1表示空
    if ((s_int == "" || s_int == "0") && (s_dot == "" || s_dot == "0")) //表示 0
    {
        str = "0.";
        str.insert(2, n, '0');
        str = str + "*10^0";
        return str;
    }

    if (s_dot.empty())
    {
        //整数 123
        char ex[3];
        sprintf(ex, "%d", s_int.length());
        string exstr(ex, strlen(ex));
        if (n <= s_int.length())
            str = "0." + s_int.substr(0, n) + "*10^" + exstr;
        else
        {
            string zero_tail;
            zero_tail.assign(n - s_int.length(), '0');
            str = "0." + s_int.substr(0, n) + zero_tail + "*10^" + exstr;
        }
    }
    else
    {
        //123.456 0.01234
        // s_dot = s_int + s_dot;
        if (s_int == "0") //0.01234
        {
            int not_zeropos = s_dot.find_first_not_of("0");
            char ex[3];
            sprintf(ex, "%d", not_zeropos);
            string exstr(ex, strlen(ex));

            if (n <= s_dot.length() - not_zeropos)
            {
                if (exstr != "0")
                    str = "0." + s_dot.substr(not_zeropos, n) + "*10^-" + exstr;
                else if (exstr == "0")
                    str = "0." + s_dot.substr(not_zeropos, n) + "*10^" + exstr;
            }
            else
            {
                string zero_tail;
                zero_tail.assign(n - s_dot.length() + not_zeropos, '0');
                if (exstr != "0")
                    str = "0." + s_dot.substr(not_zeropos, n) + zero_tail + "*10^-" + exstr;
                else
                    str = "0." + s_dot.substr(not_zeropos, n) + zero_tail + "*10^" + exstr;
            }
        }
        else //123.456
        {
            char ex[3];
            sprintf(ex, "%d", s_int.length());
            string exstr(ex, strlen(ex));
            s_dot = s_int + s_dot;
            if (n <= s_dot.length())
                str = "0." + s_dot.substr(0, n) + "*10^" + exstr;
            else
            {
                string zero_tail;
                zero_tail.assign(n - s_dot.length(), '0');
                str = "0." + s_dot.substr(0, n) + zero_tail + "*10^" + exstr;
            }
        }
    }

    return str;
}
int main()
{

    cin >> n;
    string s, c;
    cin >> s >> c;
    s = solve(s, n);
    c = solve(c, n);
    if (s == c)
        cout << "YES " << s;
    else
        cout << "NO " << s << " " << c;

    return 0;
}

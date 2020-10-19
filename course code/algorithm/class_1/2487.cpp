#include <iostream>
#include <cstdio>
using namespace std;
bool makepair(int &n, string &ans)
{
    bool flag = true;
    string str;
    if (n >= 1)
    {
        --n;
        cin >> str;
    }
    else
        return false;
    if (str == "pair")
    {
        ans = ans + "pair";
        ans += "<";
        flag &= makepair(n, ans);
        ans += ",";
        flag &= makepair(n, ans);
        ans += ">";
        return flag;
    }
    else
    {
        ans += "int";
        return flag;
    }
}

int main()
{

    int t, n;
    cin >> t;
    while (t--)
    {
        scanf("%d", &n);
        string ans;
        if (n == 1 || n & 1 == 0)
        {
            while (n--)
                cin >> ans;
            cout << "Error occurred" << endl;
            continue;
        }

        if (makepair(n, ans) && n == 0)
            cout << ans << endl;
        else
        {
            while (n--)
                cin >> ans;
            cout << "Error occurred" << endl;
        }
    }
    return 0;
}
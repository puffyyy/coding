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
char b[1000001], a[1000001];
int main()
{
    int t;
    cin >> t;
    while (t--)
    {
        bool flag = false, galf = false;
        int cnt = 0, to0 = 0, to1 = 0;
        scanf("%s %s", b, a);
        for (int i = 0; i < strlen(b); ++i)
        {

            if (b[i] == '1')
                flag = true;
            else
                galf = true;
            if (b[i] == '0' && a[i] == '1')
                to1++;
            else if (b[i] == '1' && a[i] == '0')
                to0++;
        }
        cnt = max(to1, to0);
        if (flag && galf)
            cout << cnt << endl;
        else
            cout << "-1" << endl;
    }

    return 0;
}
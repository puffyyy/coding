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
char str[100000];
int t;
void wr(long long x);
int rd();
int work(int m)
{
    int i = 0, j = 1, l;
    while (i < m && j < m)
    {
        for (l = 0; l < m; l++)
            if (str[(i + l) % m] != str[(j + l) % m])
                break;
        if (str[(i + l) % m] > str[(j + l) % m])
            i = i + l + 1;
        else
            j = j + l + 1;
        if (i == j)
            j = i + 1;
    }
    if (i < j)
        return i;
    return j;
}
int main()
{
    scanf("%d", &t);
    while (t--)
    {
        scanf("%s", str);
        int len = strlen(str);
        int p = work(len);
        for (int i = p; i < len; i++)
        {
            putchar(str[i]);
        }
        for (int i = 0; i < p; i++)
        {
            putchar(str[i]);
        }
        putchar('\n');
    }
    return 0;
}
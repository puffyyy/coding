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
const int MS = 2e5 + 5;
char str[MS];
int minest_(char str[], int n)
{
    int i = 0, j = 1, bias = 0;
    while (i < n && j < n)
    {
        if (str[i] > str[j])
            i = j++;
        else if (str[i] < str[j])
            ++j;
        else
        {
            for (bias = 1; bias <= n && j < n; bias++)
            {
                if (str[i + bias] == str[j + bias])
                    continue;
                if (str[i] > str[j + bias])
                {
                    i = bias + j;
                    j += bias;
                }
                if (str[i + bias] > str[j + bias])
                    i = j;
                ++j;
                break;
            }
        }
        if (bias > n)
            j += bias;
    }
    return i;
}
int minest(char a[], int len)
{
    int i = 0, j = 1, l;
    char *str = (char *)malloc(sizeof(char) * 2 * (len + 1));
    for (int i = 0; i < len; i++) //倍增
    {
        str[i + len] = str[i] = a[i];
    }
    while (i < len && j < len)
    {
        for (l = 0; l < len; l++)
            if (str[i + l] != str[j + l])
                break;
        if (str[i + l] > str[j + l])
            i += l + 1;
        else
            j += l + 1;
        if (i == j)
            j += 1;
    }
    return (i > j ? j : i);
}
int main()
{
    int t;
    scanf("%d", &t);
    while (t--)
    {
        scanf("%s", str);
        int n = strlen(str);
        for (int i = 0; i < n; i++) //倍增
        {
            str[i + n] = str[i];
        }
        int start = minest(str, n);
        for (int i = start; i < start + n; i++)
            putchar(str[i]);
        putchar('\n');
    }
    return 0;
}
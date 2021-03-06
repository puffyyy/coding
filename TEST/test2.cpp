#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cmath>
#include <cstdlib>
#include <vector>
#include <queue>
using namespace std;
typedef long long ll;
const int maxn = 1e6 + 5;
int mynext[maxn];
char ss[maxn];
void getnext(char t[], int mynext[])
{
    int i = 0, j = -1;
    mynext[i] = j;
    while (t[i] != '\0')
    {
        if (j == -1 || t[i] == t[j])
        {
            i++, j++;
            mynext[i] = j;
        }
        else
            j = mynext[j];
    }
    mynext[i + 1] = 0;
}
int kmp(char s[], char t[])
{
    int i = 0, j = 0;
    getnext(t, mynext);
    while (s[i] != '\0' && t[i] != '\0')
    {
        if (s[i] == t[j])
            i++, j++;
        else
            j == 0 ? i++ : (j = mynext[j]);
    }
    if (t[j] == '\0')
        return 1;
    else
        return -1;
}
char str[maxn];
int main()
{
    scanf("%s", ss);
    int len = strlen(ss);
    int n;
    scanf("%d", &n);
    while (n--)
    {
        scanf("%s", str);
        int lb = strlen(str);
        if (len == lb)
        {
            if (strcmp(str, ss) == 0)
                printf("self\n");
            else
                printf("cousin\n");
        }
        else if (len > lb)
        {
            if (kmp(ss, str) == 1)
                printf("son\n");
            else
                printf("nephew\n");
        }
        else
        {
            if (kmp(str, ss) == 1)
                printf("father\n");
            else
                printf("uncle\n");
        }
    }
    return 0;
}
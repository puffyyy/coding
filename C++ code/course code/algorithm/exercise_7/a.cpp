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
char a[1005], b[1005];
bool cmp(char a[], char b[], int l)
{
    for (int i = 0; i < l; i++)
        if (a[i] != b[i])
            return false;
    return true;
}
bool check(char a[], char b[], int la, int lb)
{
    if (la != lb)
        return false;
    else if (la & 1 == 1)
    {
        return cmp(a, b, la);
    }
    else
    {
        return (check(a, b, la / 2, lb / 2) && check(a + la / 2, b + lb / 2, la / 2, lb / 2)) || (check(a, b + lb / 2, la / 2, lb / 2) && check(a + la / 2, b, la / 2, lb / 2));
    }
}
int main()
{
    scanf("%s%s", a, b);
    printf(check(a, b, strlen(a), strlen(b)) ? "similar\n" : "not similar\n");
    return 0;
}
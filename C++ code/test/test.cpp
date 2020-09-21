#include <stdio.h>
#include <iostream>
#include <algorithm>
#include <string.h>
#include <ctype.h>
#include <queue>
#define INF 0x7ffffff
using namespace std;
typedef long long int ll;
ll a[100]; //递推题目都开ll比较保险
int main()
{
    a[1] = 1;
    a[2] = 2;
    a[3] = 3;
    for (int i = 4; i < 60; i++)
    {
        a[i] = a[i - 1] + a[i - 2];
    }
    int n;
    while (cin >> n)
    {
        cout << a[n] << endl;
    }
    return 0;
}
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

int a[45][45];
int main()
{
    //ios::sync_with_stdio(false);
    //cin.tie(nullptr);
    int cnt = 1;
    for (int i = 1; i <= 39; i++)
    {
        for (int j = 1; j <= i; j++)
        {
            int y = j;
            int x = i - j + 1;
            a[y][x] = cnt++;
        }
    }
    for (int i = 1; i <= 39; i++)
    {
        for (int j = 1; j <= 39; j++)
            printf("%3d ", a[i][j]);
        printf("\n");
    }
    printf("\n%d\n", a[20][20]);
    return 0;
}
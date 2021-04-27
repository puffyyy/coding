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
typedef long long int ll;
const int MS = 1e5 + 5;
int a[12], b[12];
/*
数位DP。
首先将问题转换成solve(R)−solve(L)的形式，这样只需要求不超过n的满足条件的数的个数。
定义dp[k][x][f1][f2][f3][f4]，其中k表示位数，x表示尾数
f1表示第k位与第k−1位是否相同
f2表示是否出现过三连
f3表示4,8的出现情况（00,01,10,11）
f4表示是否在第k位达到上限。
考虑第k+1位的每种取值i。
若i=x，则f1=1；若已有三连或原f1=1且i=x，则f2=1；若i等于4或8，改变f3；若在第k位就达到上限且i等于n的第k+1位，则f4=1。
用队列进行转移或循环每一维即可解决。
*/
int main()
{
    //ios::sync_with_stdio(false);
    char s1[15], s2[15];
    scanf("%s%s", &s1, &s2);
    for (int i = 0; i < 11;++i)
    {
        a[i+1] = s1[i] - '0';
        b[i+1] = s2[i] - '0';
    }
    

        return 0;
}
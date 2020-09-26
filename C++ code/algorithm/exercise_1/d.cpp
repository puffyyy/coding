#include <iostream>
#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include <stack>
#include <queue>
/*
先找到从后向前数，第一个降序的位置，把此位置后面的翻转。再把这个降序数字和后面第一个比它大的位置交换即可。
如果从第n个数字到最后都是递减的并且第n-1个数字小于第n个
说明从第n个数字开始的这段序列是字典序组合的最后一个
在下一个组合中他们要倒序变为字典序第一个
然后从这段序列中找出第一个大于第n-1个数字的数和第n-1个数字交换就可以了。
*/
using namespace std;
int tmp;

int main()
{
    int t;
    cin >> t;
    while (t--)
    {
        int n;
        cin >> n;
        vector<int> a;
        for (int i = 0; i < n; i++)
        {
            scanf("%d", &tmp);
            a.push_back(tmp);
        }
        vector<int> b;
        for (int i = n; i > 0; i--)
            b.push_back(i);
        if (a == b)
        {
            printf("N0NE\n");
            continue;
        }
        next_permutation(a.begin(), a.end());
        if (a == b)
        {
            printf("N0NE\n");
            continue;
        }
        next_permutation(a.begin(), a.end());

        for (int i = 0; i <= a.size() - 1; i++)
            cout << a[i] << " ";
        cout << endl;
    }
    return 0;
}
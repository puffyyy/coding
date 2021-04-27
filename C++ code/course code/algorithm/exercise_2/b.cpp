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
int n;
struct book
{
    int time;
    int no;
} books[MS];
inline bool rule_cmp(book x, book y)
{
    if (x.time != y.time)
        return x.time > y.time;
    return x.no < y.no;
}
string str[7] = {"1CLR", "AAA1", " CVP2", "E33V", "ICM1", "NIP5"};
int main()
{
    cin >> n;
    string tmp;
    for (int i = 0; i < n; ++i)
    {
        scanf("%d", &books[i].time);
        cin >> tmp;
        for (int j = 0; j < 6; ++j)
        {
            if (tmp[0] == str[j][0])
            {
                books[i].no = j;
                break;
            }
        }
    }
    sort(books, books + n, rule_cmp);
    for (int i = 0; i < n; i++)
    {
        printf("%d ", books[i].time);
        cout << str[books[i].no];
        putchar('\n');
    }
    return 0;
}
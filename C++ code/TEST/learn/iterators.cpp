
#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include <list>
#include <stack>
#include <queue>
#include <set>
using namespace std;
typedef long long int ll;
const int MS = 1e5 + 5;
template <typename IteratorType, typename elempType>
IteratorType findi(IteratorType first, IteratorType last, const elempType &value)
{
    for (; first != last; ++first)
        if (value == *first)
            return first;
    return last;
}
int main()
{
    //ios::sync_with_stdio(false);
    int a[8] = {1, 1, 2, 3, 5, 8, 13, 21};
    vector<int> vec(a, a + 8);
    list<int> li(a, a + 8);
    list<int>::iterator pos;
    list<int>::iterator li_end = li.end();
    cout << findi(a, a + 8, 1024) - a << endl;
    cout << findi(vec.begin(), vec.end(), 1024) - vec.begin() << endl;
    pos = findi(li.begin(), li.end(), 1024);
    find_if(li.begin(), li.end(), [] {});
    return 0;
}
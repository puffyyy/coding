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

int main()
{
    //ios::sync_with_stdio(false);
    int a[] = {1, 2, 2, 5, 6};
    cout << lower_bound(a, a + 5, 1) - a;
    return 0;
}
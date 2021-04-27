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

struct ss
{
    int a;
    ss(int x = 0) : a(x) {}
    bool operator<(const ss &b) const
    {
        return a < b.a;
    }
};
priority_queue<ss, vector<ss>, less<int>> heap;
int main()
{
    //ios::sync_with_stdio(false);
    //cin.tie(nullptr);
    ss c;
    c.a = 2;
    ss b;
    b.a = 5;
    heap.push(c);
    heap.push(b);
    cout << heap.top().a;
    return 0;
}
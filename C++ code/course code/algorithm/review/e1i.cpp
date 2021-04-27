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
const int MS = 1e4 + 5;
struct node
{
    int x, y, no, to, f;
    double deg;
} po[MS];
int n;
void caldeg(int left, int right)
{
    for (int i = left + 1; i <= right; i++)
    {
        if (po[left].x == po[i].x)
            po[i].deg = 2147483647;
        else
        {
            po[i].deg = 1.0 * (po[i].y - po[left].y) / (po[i].x - po[left].x);
        }
    }
}
bool cmpangle(node &a, node &b)
{
    return a.deg < b.deg;
}
bool cmpans(node &a, node &b)
{
    return ((a.f == b.f) ? (a.no < b.no) : (a.f > b.f));
}
void divide(int left, int right)
{
    if (right <= left)
        return;
    if (right - left == 1)
    {
        po[left].to = po[right].no;
        po[right].to = po[left].no;
        return;
    }
    int pos = left;
    for (int i = left + 1; i <= right; i++)
    {
        if (po[i].x < po[pos].x)
            pos = i;
        else if (po[i].x == po[pos].x && po[i].y < po[pos].y)
            pos = i;
    }
    swap(po[left], po[pos]);
    caldeg(left, right);
    sort(po + left + 1, po + right + 1, cmpangle);
    int cnt = po[left].f;
    for (int i = left + 1; i <= right; i++)
    {
        // if(po[i].to!=0)
        cnt += po[i].f;
        if (cnt == 0)
        {
            po[left].to = po[i].no;
            po[i].to = po[left].no;
            divide(left + 1, i - 1);
            divide(i + 1, right);
            return;
        }
    }
}
int main()
{
    cin >> n;
    for (int i = 0; i < 2 * n; i++)
    {
        cin >> po[i].x >> po[i].y >> po[i].no;
        po[i].f = (i < n) ? 1 : -1;
    }
    divide(0, 2 * n - 1);
    sort(po, po + 2 * n, cmpans);
    for (int i = 0; i < n; i++)
        cout << po[i].to << " ";
    return 0;
}
#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <cstdlib>
#include <algorithm>
#include <vector>
using namespace std;
const int MS = 1e6 + 5;
int n;
struct LOC
{
    double x, y, z;

    bool operator<(const LOC &o) const
    {
        return x < o.x;
    }
} loc[MS];
bool cmpy(const LOC &a, const LOC &b)
{
    return a.y < b.y;
}
double getdis(LOC a, LOC b)
{
    return sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2) + pow(a.z - b.z, 2));
}
double divide(int left, int right)
{
    if (left >= right)
        return 0x7fffffff;
    if (left + 1 == right)
        return getdis(loc[left], loc[right]);
    else if (left + 2 == right)
    {
        double dist1 = getdis(loc[left], loc[left + 1]);
        double dist2 = getdis(loc[left], loc[left + 2]);
        double dist3 = getdis(loc[left + 1], loc[left + 2]);
        return min(min(dist1, dist2), dist3);
    }
    else
    {
        int mid = (left + right) >> 1;
        double ll = divide(left, mid);
        double rr = divide(mid + 1, right);
        double delta = min(ll, rr);
        vector<LOC> res;
        for (int i = left; i < right; ++i)
        {
            if (fabs(loc[i].x - loc[mid].x) < delta)
                res.push_back(loc[i]);
        }
        sort(res.begin(), res.end(), cmpy);
        for (int i = 0; i < res.size() - 1; ++i)
        {
            for (int j = i + 1; j < res.size(); ++j)
            {
                if (res[j].y - res[i].y >= delta)
                    break;
                if (res[j].z - res[j].z >= delta)
                    continue;
                double d_ij = getdis(res[i], res[j]);
                if (d_ij < delta)
                    delta = d_ij;
            }
        }
        return delta;
    }
}
int main()
{
    scanf("%d", &n);
    register int i;
    for (i = 0; i < n; ++i)
    {
        scanf("%lf%lf%lf", &loc[i].x, &loc[i].y, &loc[i].z);
    }
    sort(loc, loc + n);
    double ans = divide(0, n - 1);
    printf("%.4lf", ans);
    return 0;
}
/*
6
1.0 1.5 1.0
0 0 0
0 1 1
2 0 0
0 0 1
1 1 1
*/
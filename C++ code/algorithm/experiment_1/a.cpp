#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;
const int MAXSIZE = 1e5 + 2;
int temp[MAXSIZE];
int a[MAXSIZE];
long long merge(int a[], int ll, int mid, int rr)
{
    long long cnt = 0;
    int i, j;
    for (i = ll; i <= rr; ++i)
    {
        temp[i] = a[i];
    }
    i = ll;
    j = mid + 1;
    int pos = ll;
    for (; i <= mid && j <= rr; ++pos)
    {
        if (temp[i] <= temp[j])
        {
            a[pos] = temp[i++];
        }
        else
        {
            a[pos] = temp[j++];
            cnt += mid - i + 1;
        }
    }
    if (i <= mid)
        while (i <= mid)
            a[pos++] = temp[i++];
    else
        while (j <= rr)
            a[pos++] = temp[j++];
    return cnt;
}

long long mergesort(int a[], int l, int r)
{
    if (r <= l)
        return 0;
    int mid = (l + r) / 2;

    long long lcnt = mergesort(a, l, mid);
    long long rcnt = mergesort(a, mid + 1, r);

    long long cnt = merge(a, l, mid, r);
    return cnt + lcnt + rcnt;
}
int main()
{
    int n;
    cin >> n;
    for (int i = 0; i < n; ++i)
        scanf("%d", &a[i]);

    cout << mergesort(a, 0, n - 1) << endl;
    return 0;
}

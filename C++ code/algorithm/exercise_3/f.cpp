#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <cstdlib>
using namespace std;
typedef long long int ll;
int cnt;
int a[100005], flag[100005];
void swapa(int i, int j)
{
    int tmp = a[i];
    a[i] = a[j];
    a[j] = tmp;
    ++cnt;
}
int main()
{
    int n;
    scanf("%d", &n);
    a[0] = 1;
    for (int i = 1; i <= n; ++i)
        scanf("%d", &a[i]);

    for (int i = 1; i <= n; ++i)
    {
        if (a[i] == i)
        {
            swapa(i + 1, i);
            flag[i] = 0;
            if (a[i + 1] == i + 1)
                flag[i + 1] = 1;
            else
                flag[i + 1] = 0;
        }
    }
    printf("%d\n", cnt);
    return 0;
}
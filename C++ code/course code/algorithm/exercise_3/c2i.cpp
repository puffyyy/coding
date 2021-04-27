#include <cstdio>
#include <cstdlib>
#include <algorithm>
using namespace std;
typedef long long ll;
const int MS = 1e5 + 5;
int a;
int cnt[MS];
int main()
{
    int n;
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
    {
        scanf("%d", &a);
        cnt[a] += 1;
    }
    for (int i = 0; i < MS; i++)
        cnt[i] = max(cnt[i - 1], cnt[i - 2] + cnt[i] * i);
    printf("%d", cnt[MS - 1]);
    return 0;
}
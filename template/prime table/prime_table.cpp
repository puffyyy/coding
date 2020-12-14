#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef long long ll;
#define maxm 1000005
#define mod 1000000007
const int N = 1e8 + 10;
int n, q, prime[N], pcnt;
int not_prime[N];
void makeTable(int maxn)
{
    not_prime[1] = 1;
    for (int i = 2; i <= maxn; ++i)
    {
        if (!not_prime[i])
            prime[++pcnt] = i;   
        for (int j = 1; j <= pcnt; ++j)
        {
            if (i * prime[j] > maxn)
                break;
            not_prime[i * prime[j]] = 1;
            if (i % prime[j] == 0)
                break;
        }
    }
}
int main()
{
    makeTable(1002);
    for (int i = 1; i <= pcnt; i++)
        printf("%d ", prime[i]);
    return 0;
}
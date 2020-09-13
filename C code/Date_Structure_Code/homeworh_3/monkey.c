#include <stdio.h>
#include <stdlib.h>
int main()
{
    int n, m, s=0,q;   
    scanf("%d%d%d", &n, &m, &q);
    for (int i=2; i<=n; i++) {
        if (m >= i) s = s + m % i;
        else s = s + m;
        if (s >= i) s -= i;
    }
    printf("%d",(s+q-1)%n+1);
    return 0;
}
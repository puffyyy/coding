#include<stdio.h>
#include<stdlib.h>
long long binarypow(int a,int n)
{
    if(n==0)return 1;
    else if(n&1)return a*binarypow(a,n-1);
    else {
        long long ans=binarypow(a,n>>1);
        return ans*ans;
    }
}
long long quickpow(int a,int n)
{
    long long  ans=1;
    while(n>0)
    {
        if(n&1)
            ans*=a;
        a*=a;
        n>>=1;
    }
    return ans;
}
int main()
{
    printf("%lld",quickpow(5,2));
    return 0;
}
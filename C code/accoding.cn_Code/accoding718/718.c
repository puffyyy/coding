#include<stdio.h>

long long  a[251]={0,1,3,5,11};
long long  fun(int n)
{
    if(a[n]!=0)return a[n];
    else return a[n]=fun(n-1)+2*fun(n-2);
}
int main ()
{
    int n;
    while(~scanf("%d",&n))
    printf("%lld\n",fun(n/3));
    return 0;
}
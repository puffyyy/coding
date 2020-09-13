#include<stdio.h>
#include<stdlib.h>
int a[100005];
int main()
{
    int n;
    while(~scanf("%d",&n)){
        long l=0,r=0;
        int i,j;
        for(i=1;i<=n;i++)
        scanf("%d",&a[i]);
        
        for(i=0,j=n+1;i!=j-1;){
            if(l>r){
                l-=r,r=0;
                r+=a[-1+j--];
            }
            else if(l<r){
                r-=l;
                l=0;
                l+=a[1+i++];
            }
            else {
                r=0;
                l=a[1+i++];
            }
        }
        printf("%d %d\n",i,n-i);
    }
    return 0;
}
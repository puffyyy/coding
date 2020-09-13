#include<stdio.h>
#include<stdlib.h>
long ans;
int a[100002],b[100002];
inline void swap(int *a,int *b)
{
    int temp;
    temp=*a;
    *a=*b;
    *b=temp;
}
int main(int argc,char *argv[])
{
    int m,n,k;
    while(~scanf("%d%d%d",&n,&m,&k)){
        for(int i=1;i<=n;i++)
        {
            scanf("%d",&b[i]);//第i位置的应用序号
            a[b[i]]=i;// 编号为n的应用位置
        }
        ans=0;
        int query;
        for(int i=0;i<m;i++){
            scanf("%d",&query);
            ans+=(a[query]-1)/k;
            if(a[query]!=1){
                int ta=a[query];
                swap(&b[ta-1],&b[ta]);
                swap(&a[b[ta-1]],&a[b[ta]]);
            }
        }
        ans+=(long)m;
        printf("%lld\n",ans);
    }
   return 0;
}
#include <stdio.h>
#include <stdlib.h>
int n,ans[21],flag[21];
void perm(int i)
{
    int j,k;
    if(i==n){
        for(k=0;k<n;k++)
            printf("%d ",ans[k]);
        putchar('\n');
    }
    else {
        for(j=1;j<=n;j++)
        {
            if(!flag[j]){
                ans[i]=j;
                flag[j]=1;
                perm(i+1);
                flag[j]=0;
            }
        }
    }
}

void swap(int *a,int *b)
{
    int temp;
    temp=*a;
    *a=*b;
    *b=temp;
}
void dic(int n)
{

    int i,j,k,r;
    for(i=1;i<=n;i++)
        ans[i]=i;
    for(k=1;k<=n;k++)
        printf("%d ",k);
    putchar('\n');
    while(1)
    {
        for(i=n-1;i>=1;i--)
            if(ans[i]<ans[i+1])break;
        if(i<1)return;
        j=i+1;
        k=ans[i]+1;
        for(k=ans[i]+1;k<=n;k++)
           {
               for(j=i+1;j<=n;j++)
                    if(ans[j]==k)break;
               if(ans[j]==k)break;
           }
        swap(&ans[i],&ans[j]);
        r=n;
        for(k=i+1;k<=r;k++,r--)
            swap(&ans[k],&ans[r]);
        for(k=1;k<=n;k++)
            printf("%d ",ans[k]);
        putchar('\n');
    }
}
int main()
{
    int p,q;
    scanf("%d",&n);
    //perm(0);
    dic(n);
    return 0;
}


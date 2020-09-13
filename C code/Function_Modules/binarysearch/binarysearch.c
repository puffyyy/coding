#include <stdio.h>
#include <string.h>
int a[100001];
int binarysearch_left(int lenth,int x)
{
    int left=0,right=lenth-1;
    while(left<=right){
        int mid=left+((right-left)>>1);
        if(a[mid]>=x)
            right=mid-1;
        else left=mid+1;
    }
    if(a[left]==x)return left;
    else return -1;
}
int binarysearch_right(int lenth,int x)
{
    int left=0,right=lenth-1,mid;
    while(left<=right){
        mid=left+((right-left)>>1);
        if(a[mid]<=x)
            left=mid+1;
        else right=mid-1;
    }
    if(a[right]==x)return right;
    else return -1;
}
int main()
{   
    int n,i,t;
    scanf("%d",&n);
    for(i=0;i<n;i++)
        scanf("%d",&a[i]);
    scanf("%d",&t);
    for(;t>0;t--)
    {
        scanf("%d",&i);
        if(binarysearch_left(n,i)!=-1)
        printf("%d %d\n",binarysearch_left(n,i)+1,binarysearch_right(n,i)+1);
        else printf("-1\n");
    }

    return 0;
}
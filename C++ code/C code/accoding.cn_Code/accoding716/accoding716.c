#include<stdio.h>//https://blog.csdn.net/u013309870/article/details/70978279
int a[1001];//积水问题
int n;
int main ()
{
    
    while(~scanf("%d",&n))
    {
        int ans=0;
        int left=0,right=n-1;
        
        for(int i=0;i<n;i++){
            scanf("%d",&a[i]);
        }
        int lmax=a[left],rmax=a[right];
        while(left<right){
            if(a[left]<a[right]){
                left++;
                if(a[left]<lmax)ans+=lmax-a[left];
                else {
                    lmax=a[left];
                }
            }
            else {
                right--;
                if(a[right]<rmax)ans+=rmax-a[right];
                else {
                    rmax=a[right];
                }
            }

        }
        
        printf("%d\n",ans);
    }
    return 0;
}
#include<stdio.h>
#include<stdlib.h>
int buf[10001];
void swap(int *a,int *b)
{
    int temp=*a;
    *a=*b;
    *b=temp;
}
void quicksort(int a[],int start,int end)
{
    if(start>=end)return ;
    int mid=start+(end-start)/2;
    if(a[mid]>a[start])swap(&a[mid],&a[start]);
    if(a[start]>a[end])swap(&a[start],&a[end]);
    int index=a[start];         //找三个数中较中间的为基准
    int i=start,j=end;
    while(i<j){
        while(a[j]>=index&&i<j)j--;
        while(a[i]<=index&&i<j)i++;
        if(i<j)swap(&a[i++],&a[j--]);
    }
    swap(&a[start],&a[j]);
    quicksort(a,start,j-1);
    quicksort(a,j+1,end);
}
int main(){

    int n;
    scanf("%d",&n);
    for(int i=0;i<n;i++)scanf("%d",&buf[i]);
    quicksort(buf,0,n-1);
    for(int i=0;i<n;i++)printf("%d ",buf[i]);

    return 0;

}
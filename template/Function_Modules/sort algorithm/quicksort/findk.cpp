#include<iostream>
#include<cstdio>
using namespace std;
long long int a[2000001];
int Partition(long long int A[],int left,int right)
{
	int temp=A[left];
	while(left<right)
	{
		while(left<right&&A[right]>temp)
			right--;
		A[left]=A[right];
		while(left<right&&A[left]<=temp)
		    left++;
		A[right]=A[left];
	}
	A[left]=temp;
	return left;
}
int quickSort(long long int A[],int left,int right,int k)
{
	if(left<right)
	{
		int pos=Partition(A,left,right);
		if(pos>k)
		    return quickSort(A,left,pos-1,k);
		else if(pos<k)
		    return quickSort(A,pos+1,right,k);
		else
		    return pos;
	}
}
int main()
{
	int k,n;
	cin>>n;

	for(int i=0;i<n;i++)
	{
		scanf("%d",&a[i]);
	}
	cin>>k;
	int kpos=quickSort(a,0,n-1,k-1);
	cout<<a[kpos];
 }

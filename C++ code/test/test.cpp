#include<cstdio>
#include<iostream>
using namespace std;
#define max(a,b) (a>b?a:b)
int n,ans=0;

bool canThreePartsEqualSum(int* A, int ASize){

        int i=0,j=ASize-1,a=0,c=0,sum=0;
        for(int k=0;k<ASize;k++) 
		sum+=A[k];
        
        if(sum%3!=0)return false;
        int tr=sum/3;
        for(;i<j;){
            if(a==tr&&c==tr)return true;
            if(a!=tr)a+=A[i++];
            if(c!=tr)c+=A[j--];
        }
        return false;
}
int main(){
	int A[100]={1,-1,1-1};
	cout<<canThreePartsEqualSum(A,4);
	return 0;
}


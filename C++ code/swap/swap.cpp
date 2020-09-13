#include<iostream>
#include<cstdio>
using namespace std;
void swap2(int *a,int *b)
{
    int temp;
    temp=*a;
    *a=*b;
    *b=temp;
}
void swap1(int &a,int &b)
{ 
    int temp=a;
    a=b;
    b=temp;
}
int main ()
{
    int a,b;
    while(~scanf("%d %d",&a,&b))
    {
        swap1(a,b);
        printf("%d %d\n",a,b);
        swap2(&c,&d);
        printf("%d %d\n",c,d);

    }


}
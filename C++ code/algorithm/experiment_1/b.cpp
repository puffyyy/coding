#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;
int n;
int main()
{
   while(~scanf("%d",&n)){
    int cnt=0;
    int deg=0;
    while(true)
    {
        cnt++;
        deg+=n;
        deg=deg%360;
        if(deg==0)
            break;
    }
    printf("%d\n",cnt);
}
    return 0;
}

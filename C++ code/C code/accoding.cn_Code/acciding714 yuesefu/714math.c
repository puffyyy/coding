#include <stdio.h>//https://blog.csdn.net/u011500062/article/details/72855826?depth_1-utm_source=distribute.pc_relevant.none-task&utm_source=distribute.pc_relevant.none-task
#include <stdlib.h>
int f(int n,int m)//递归
{
    if(n==1)return 0;
    else return (f(n-1,m)+m)%n;
}
int main()
{
    int n, m, s=0;   
    scanf("%d%d", &n, &m);
    for (int i=2; i<=n; i++) {//迭代  //优化取模
        /*if (m >= i) s = s + m % i;
        else s = s + m;
        if (s >= i) s -= i;*/
        s=(s+m)%i;//正常迭代
    }
    printf("%d",s+1);
    return 0;
}
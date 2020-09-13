#include <stdio.h>
#include <string.h>
int a[101][101]; //球一样，盒子一样，可空盒
void dp1(int m, int n); //a[i][j]求解的是数字i分为j份的全部方案 
void dp2(int m, int n); // a[i][j]求解的是整数i分解成不大于j的全部方案
int main()              //结果居然可以相同？？？
{
    int m, n, t;
    long ans = 0;
    scanf("%d",&t);//t组数据
    for(;t>0;t--)
    {
    scanf("%d%d", &m, &n);
    ///*
    int i;
    dp1(m, n);
    for (i = 1; i <= n; i++){//求和 将所有盒子的情况无论空满均算入方案
        ans += a[m][i];
    }
    printf("dp1:%ld\n", ans);
    //*/
    memset(a, 0, sizeof(int));
    dp2(m, n);
    printf("%ld\n", a[m][n]);
    }
    return 0;
}
void dp1(int m, int n)       //a1+a2+...+an-1+an=m    两种情况：1.a1==1  a[i - 1][j - 1] 
{                            //                       2. "a1>=2 a_1-1+a_2-1+...+(a_n-1)-1+a_n-1=m-n" 退化为数m-n划分为n个数之和的方案数  a[i - j][j]
    int i, j;
    for (i = 1; i <= m; i++)
        for (j = 1; j <= n; j++)
        {
            if (j == 1 || j == i)
                a[i][j] = 1;
            else if (j > i)
                a[i][j] == 0;
            else
                a[i][j] = a[i - 1][j - 1] + a[i - j][j];
        }
}
void dp2(int m, int n)
{
    int i, j;
    for (i = 1; i <= m; i++)
        for (j = 1; j <= n; j++)
        {
            if (i == 1 || j == 1)//表示 对1的划分，那么只有一种划分方式 1
                a[i][j] = 1;
            else if (i < j)//当m=1时其实就是把让所有加数小于等于1，那就是所有加数都是1,一种方案
                a[i][j] = a[i][i];
            else if (i == j)//分两种情况：1.1.拆分数不包括j，即退化为a[i][j - 1] 2.拆分数包括j 且i==j,即一种方案 +1
                a[i][j] = a[i][j - 1] + 1;
            else//分两种情况：1.拆分数不包括j，即退化为a[i][j - 1] 2.拆分数包括j 则转化为数i-j分解为不大于j的方案数
                a[i][j] = a[i][j - 1] + a[i - j][j];
        }
}
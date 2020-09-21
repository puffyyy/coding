#include <iostream>
using namespace std;
int a[90] = {
    0,
    2,
    2,
    4,
    6,
    10,
    16,
    26,
};
int fun(int n)
{
    if (n <= 0)
        return 0;
    if (a[n] != 0)
        return a[n];

    a[n] = fun(n - 1) + fun(n - 2) - fun(n - 12);
    return a[n];
}
int main()
{
    int n, t;
    cin >> t;
    while (t--)
    {
        scanf("%d", &n);
        if (n > 20)
            printf("%d\n", fun(n) - fun(n - 20));
        else
            printf("%d\n", fun(n));
    }
    return 0;
}
/*
通过递推得知，在3-12年的时候艾露猫正在成年期，每年都会生小猫，一对成年猫生一对小猫，即c a t [ i ] = c a t [ i − 1 ] + c a t [ i − 2 ] cat[i] = cat[i-1]+cat[i-2]cat[i]=cat[i−1]+cat[i−2]，当年喵喵的数量是上一年喵喵的数量加上2年前的猫的数量(即为新出生的猫，两年前的猫刚刚成年生小猫)；
可惜的是13年之后，艾露猫老了 不能生小猫了，我们任然按照原来的模拟，但是此时要减去多生的，那么多生了多少小猫呢？自然是13年前的那一批老了的艾露猫的数量，故而此时就要c a t [ i ] = c a t [ i − 1 ] + c a t [ i − 2 ] − c a t [ i − 13 ] cat[i] = cat[i-1]+cat[i-2]-cat[i-13]cat[i]=cat[i−1]+cat[i−2]−cat[i−13]
这个题有一个坑点在于死亡,如果还按照原来的思路，
会写出c a t [ i ] = c a t [ i − 1 ] + c a t [ i − 2 ] − c a t [ i − 13 ] − c a t [ i − 20 ] cat[i] = cat[i-1]+cat[i-2]-cat[i-13]-cat[i-20]cat[i]=cat[i−1]+cat[i−2]−cat[i−13]−cat[i−20]
但是注意这显然是错误的，因为一只猫只能死一次，按照这个思路i=22的时候，第一年死的猫，第二年又死了一次，这显然是不对的，故而递推式只在c a t [ i ] = c a t [ i − 1 ] + c a t [ i − 2 ] − c a t [ i − 13 ] cat[i] = cat[i-1]+cat[i-2]-cat[i-13]cat[i]=cat[i−1]+cat[i−2]−cat[i−13]即可，我们在输入时候判断，如果n &gt; 20 n&gt;20n>20，就减去c a t [ i − 20 ] cat[i-20]cat[i−20]
*/
#include <stdio.h>
#include <stdlib.h>
int a[1002], b[1002];
int a1 = 0, cnt23 = 0, cnt32 = 0;
void swap(int *a, int *b)
{
    int tmp = *a;
    *a = *b;
    *b = tmp;
}
int main()
{
    int n, i = 0, j = 0, k = 0;
    scanf("%d", &n);
    for (i = 0; i < n; i++)
    {
        scanf("%d", &a[i]);
        b[i] = a[i];
    }
    /*
    通过三个下标遍历一遍实现的方法。
    p1从左侧开始，指向第一个非1的数字；p3从右侧开始，指向第一个非3的数字。
    p2从p1开始遍历，如果是2，p2继续遍历，直到p2遇到1或者3
    如果遇到1，则和p1进行交换，然后p1向右，指向第一个非1的数字
    如果遇到3，则和p3进行交换，然后p3向左，指向第一个非3的数字
    */
    for (i = 0, j = n - 1; i < n && k < j;)
    {
        while (b[i] == 1)
            i++;
        while (b[j] == 3)
            j--;
        for (k = i; k <= j;)
        {
            if (b[k] == 2)
            {
                k++;
                continue;
            }
            if (b[k] == 1)
            {
                swap(b + i, b + k);
            }
            else if (b[k] == 3)
            {
                swap(b + j, b + k);
            }
            break;
        }
    }
    /*
    统计本来应该是1的位置然而不是1的个数a1
    本来应该是2的位置然而是3的个数cnt23
    本来应该是3的位置是2的个数cnt32
    结果为a1+max(cnt23，cnt32)
    */
    for (i = 0; i < n; i++)
    {
        if (b[i] == 1 && a[i] != 1)
            a1++;
        if (a[i] == 3 && b[i] == 2)
            cnt23++;
        if (a[i] == 2 && b[i] == 3)
            cnt32++;
    }
    printf("%d", a1 + (cnt23 > cnt32 ? cnt23 : cnt32));
    return 0;
}
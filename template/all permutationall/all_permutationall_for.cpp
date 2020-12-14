#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

void swap(int *a, int *b)
{
    int tmp;
    tmp = *a;
    *a = *b, *b = tmp;
}

//全排列
void reverse(int a[], int len, int pos)
{
    int i, j;
    for (i = pos, j = len - 1; i < j; ++i, --j)
    {
        swap(a + i, a + j);
    }
}
int next_permutation(int a[], int len)
{
    //先找到从后向前数，第一个降序的位置，把此位置后面的翻转。再把这个降序数字和后面第一个比它大的位置交换即可。
    int i = len - 2; //最后一个数
    for (; i >= 0; i--)
        if (a[i] < a[i + 1])
            break; // pos i 为第一个降序的位置
    int j = len - 1;
    if (i < 0)
        return 0; //failed
    while (a[i] > a[j] && i < j)
        --j;
    swap(a + i, a + j);
    reverse(a, len, i + 1);
    return 1;
}

int main()
{
    int n;
    int a[20] = {0};
    scanf("%d", &n);
    int i, j;
    for (i = 0; i < n; i++)
    {
        a[i] = i + 1;
        printf("%d ", a[i]);
    }
    printf("\n");
    while (next_permutation(a, n))
    {
        for (i = 0; i < n; i++)
        {
            printf("%d ", a[i]);
        }
        printf("\n");
    }
    return 0;
}

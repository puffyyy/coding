#include <stdio.h>
#define MS 1000006
int a[MS];
void HeapFixdown(int a[], int i, int n) //向下修复小顶堆的第i个位置  n为边界size
{
    int j;
    int temp;
    temp = a[i];
    j = i + i; //左子节点
    while (j <= n)
    {

        if (j + 1 <= n && a[j + 1] < a[j]) //若为大顶堆，则改为(j + 1 <= n && a[j + 1] > a[j])
            j++;                           //在左右孩子中找最小的
        if (a[j] >= temp)                  //若为大顶堆，则改为(a[j] <= temp)
            break;
        a[i] = a[j]; //把较小的子结点往上移动,替换它的父结点
        i = j;
        j = i + i;
    }
    a[i] = temp;
}
void MakeMinHeap(int a[], int arrSize) //heap->arr数组中有元素
{
    for (int i = arrSize / 2; i > 0; i--) //对叶子结点，可以认为它已经是一个合法的堆,只需要处理他们的父节点
        HeapFixdown(a, i, arrSize);       //以每个父节点为堆顶，向下调整
}
int main()
{
    int n;
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%d", a + i);
    MakeMinHeap(a, n);
    for (int i = 1; i <= n; i++)
        printf("%d ", a[i]);
    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXSIZE 1000001
typedef int dataType;
struct Heap
{
    int size;
    dataType arr[MAXSIZE];
};
//arr[1-size]可用 arr[0]为空，不用

struct Heap *initHeap()
{
    struct Heap *heap;
    heap = (struct Heap *)malloc(sizeof(struct Heap));
    heap->size = 0;
    return heap;
}
void destoryHeap(struct Heap *heap)
{
    free(heap);
}
void HeapFixup(int a[], int i) //向上修复小顶堆的第i个位置
{
    int j, temp;
    temp = a[i];
    j = i / 2; //父结点
    while (j > 0 && i != 1)
    {
        if (a[j] <= temp) //若为大顶堆，则改为(a[j] >= temp)
            break;

        a[i] = a[j]; //下沉：把较大的子结点往下移动,替换它的子结点
        i = j;
        j = i / 2;
    }
    a[i] = temp;
}
void HeapFixdown(int a[], int i, int n) //向下修复小顶堆的第i个位置  n为边界size
{
    int j;
    dataType temp;
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
void MinHeapAddNumber(struct Heap *heap, dataType item)
{
    //if(heap->size>=MAXSIZE-1)printf("full heap\n")
    heap->arr[++heap->size] = item;
    HeapFixup(heap->arr, heap->size);
}
void MinHeapDeleteNumber(struct Heap *heap) //删除堆顶
{
    heap->arr[1] = heap->arr[heap->size--];
    HeapFixdown(heap->arr, 1, heap->size);
}
void MakeMinHeap(struct Heap *heap, int arrSize) //heap->arr数组中有元素
{
    heap->size = arrSize;
    for (int i = arrSize / 2; i > 0; i--)      //对叶子结点，可以认为它已经是一个合法的堆,只需要处理他们的父节点
        HeapFixdown(heap->arr, i, heap->size); //以每个父节点为堆顶，向下调整
}
void Minheapsort(struct Heap *heap, int n) //降序
{
    MakeMinHeap(heap, n);
    for (int i = n; i > 1; i--)
    {
        //Swap(a[i], a[1]);
        dataType tmp = heap->arr[1];
        heap->arr[1] = heap->arr[i];
        heap->arr[i] = tmp;
        HeapFixdown(heap->arr, 1, i - 1);
    }
}
int main()
{
    struct Heap *heap;
    heap = initHeap();
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
    {
        int tmp;
        scanf("%d", &tmp);
        if (tmp == 1)
        {
            scanf("%d", &tmp);
            MinHeapAddNumber(heap, tmp);
        }
        else if (tmp == 2)
        {
            printf("%d\n", heap->arr[1]);
        }
        else
        {
            MinHeapDeleteNumber(heap);
        }
    }
    return 0;
}
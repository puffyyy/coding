/* 
 Author: 杨东霖
 Result: AC	Submission_id: 2742504
 Created at: Tue Jul 21 2020 15:46:41 GMT+0800 (China Standard Time)
 Problem_id: 2369	Time: 5	Memory: 1708
*/

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define MAX(a, b) ((a) > (b) ? (a) : (b))
int n, k;
struct movie
{
    int l, v;
} a[10005];
int heap[1005];
int heapsize;
long long max = 0, time = 0;

int cmp0(const void *a, const void *b)
{
    struct movie *c = (struct movie *)a;
    struct movie *d = (struct movie *)b;
    return (c->v - d->v);
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
int deletetop()
{
    int temp = heap[1];
    heap[1] = heap[heapsize--];
    HeapFixdown(heap, 1, heapsize);
    return temp;
}
int main()
{
    FILE *fin = fopen("in.txt", "r");
    FILE *ans = fopen("ans.txt", "w");
    fscanf(fin, "%d%d", &n, &k);
    for (int i = 1; i <= n; ++i)
    {
        fscanf(fin, "%d%d", &a[i].l, &a[i].v);
    }
    qsort(a + 1, n, sizeof(a[1]), cmp0);
    for (int i = 0; i < n; i++)
        printf("%d %d\n", i, a[i].v);
    for (int i = n; i > 0; i--)
    {
        heap[++heapsize] = a[i].l;
        HeapFixup(heap, heapsize);
        time += a[i].l;
        if (heapsize > k)
            if (heap[heapsize] > heap[1])
            {
                time -= heap[1];
                heap[1] = heap[heapsize];
                heapsize--;
                HeapFixdown(heap, 1, heapsize);
            }
            else
            {
                time -= a[i].l;
                heapsize--;
            }
        if (max < time * a[i].v)
            fprintf(ans, "%d %d %d\n", i, a[i].v, time);
        max = MAX(max, time * a[i].v);
    }
    fprintf(ans, "%lld\n", max);
    return 0;
}
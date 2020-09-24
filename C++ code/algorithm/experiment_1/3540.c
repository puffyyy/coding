#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#define MAXSIZE 10000005
int arr[MAXSIZE];
void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}
void quicksort(int a[], int start, int end, int k)
{
    if (start >= end)
        return;
    int mid = start + (end - start) / 2;
    if (a[mid] > a[start])
        swap(&a[mid], &a[start]);
    if (a[start] > a[end])
        swap(&a[start], &a[end]);
    int index = a[start]; //找三个数中较中间的为基准
    int i = start, j = end + 1;
    while (i < j)
    {
        while (a[++i] > index && i < end)
            ;
        while (a[--j] < index && j > start)
            ;
        if (i < j)
            swap(&a[i], &a[j]);
    }
    swap(&a[start], &a[j]);

    if (k < j)
        quicksort(a, start, j - 1, k);
    else if (k > j)
        quicksort(a, j + 1, end, k);
    if (k == j)
    {
        return;
    }
}
int main()
{
    int t;
    scanf("%d", &t);
    while (t--)
    {
        int k, n;
        scanf("%d%d", &n, &k);
        for (int i = 0; i < n; i++)
            scanf("%d", &arr[i]);
        quicksort(arr, 0, n - 1, k - 1);
        printf("%d\n", arr[k - 1]);
    }
    return 0;
}
// 6 6 2 9 1 4 3 2 7
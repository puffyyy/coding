#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
int array[101];
void swap(int *a, int *b)
{
    int tmp = *a;
    *a = *b;
    *b = tmp;
}
int selectSort(int a[], int arraysize)
{
    int cnt = 0;
    int minpos = 0;
    for (int i = 0; i < arraysize;)
    {
        for (int j = i + 1; j < arraysize; ++j)
        {
            if (a[minpos] > a[j])
            {
                minpos = j;
            }
            ++cnt;
        }
        swap(&a[i], &a[minpos]);
        minpos = ++i;
    }
    return cnt;
}
int bubbleSort(int a[], int arraysize)
{
    int flag = 0, cnt = 0;
    for (int i = 0; i < arraysize && flag == 0; i++)
    {
        flag = 1;
        for (int j = 0; j < arraysize - i - 1; j++)
        {
            if (a[j] > a[j + 1])
            {
                swap(&a[j], &a[j + 1]);
                flag = 0;
            }
            ++cnt;
        }
    }
    return cnt;
}
void heapAdjustdown(int a[], int arraysize, int i, int *cnt)
{ //0~n-1
    int tmp = a[i];
    int j = 2 * i + 1;
    for (; j < arraysize;)
    {
        if (j + 1 < arraysize && a[j + 1] > a[j])
            ++j;
        ++(*cnt);
        if (tmp >= a[j])
            break;
        a[i] = a[j];

        i = j, j = 2 * i + 1;
    }
    a[i] = tmp;
}
void makeheap(int a[], int arraysize, int *cnt)
{

    for (int i = arraysize / 2; i >= 0; i--)
    {
        heapAdjustdown(a, arraysize, i, cnt);
    }
}
int heapSort(int a[], int arraysize)
{
    int cnt = 0;
    makeheap(a, arraysize, &cnt);
    int pos = arraysize;
    swap(&a[--pos], &a[0]);
    for (; pos > 1;)
    {
        heapAdjustdown(a, pos, 0, &cnt);
        swap(&a[--pos], &a[0]);
    }
    return cnt;
}
void merge(int a[], int left, int right, int mid, int temp[], int *cnt)
{
    int i = left, q = left;
    int j = mid + 1;
    while (i <= mid && j <= right)
    {
        ++(*cnt);
        if (a[i] <= a[j])
            temp[q++] = a[i++];
        else
            temp[q++] = a[j++];
    }
    while (i <= mid)
        temp[q++] = a[i++];
    while (j <= right)
        temp[q++] = a[j++];
    for (i = left; i <= right; i++)
        a[i] = temp[i];
}
int mergeSort(int a[], int left, int right, int temp[])
{
    int cnt = 0;
    if (left >= right)
        return 0;
    int mid = left + (right - left) / 2;
    cnt += mergeSort(a, left, mid, temp);
    cnt += mergeSort(a, mid + 1, right, temp);
    merge(a, left, right, mid, temp, &cnt);
    return cnt;
}
int quickSort(int a[], int left, int right)
{
    static int cnt = 0;
    if (left >= right)
        return 0;
    int i = left, j = left;
    for (i = left + 1; i <= right; i++)
    {
        ++cnt;
        if (a[i] < a[left])
            swap(&a[++j], &a[i]);
    }
    swap(&a[left], &a[j]);
    quickSort(a, left, j - 1);
    quickSort(a, j + 1, right);
    return cnt;
}
void printarray(int a[], int n)
{
    for (int i = 0; i < n; i++)
        printf("%d ", a[i]);
    putchar('\n');
}
int main()
{
    int temp[101];
    int n, op, ans;
    scanf("%d%d", &n, &op);
    for (int i = 0; i < n; i++)
        scanf("%d", &array[i]);

    switch (op)
    {
    case 1:
        ans = selectSort(array, n);
        printarray(array, n);
        printf("%d\n", ans);
        break;
    case 2:
        ans = bubbleSort(array, n);
        printarray(array, n);
        printf("%d\n", ans);
        break;
    case 3:
        ans = heapSort(array, n);
        printarray(array, n);
        printf("%d\n", ans);
        break;
    case 4:
        ans = mergeSort(array, 0, n - 1, temp);
        printarray(array, n);
        printf("%d\n", ans);
        break;
    case 5:
        ans = quickSort(array, 0, n - 1);
        printarray(array, n);
        printf("%d\n", ans);
        break;
    default:
        break;
    }
    return 0;
}
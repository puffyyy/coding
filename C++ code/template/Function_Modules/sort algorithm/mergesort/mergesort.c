#include <stdio.h>

void merge(int a[], int left, int right, int mid, int temp[])
{
    int i = left, q = left;
    int j = mid + 1;
    while (i <= mid && j <= right)
    {
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
void mergeSort(int a[], int left, int right, int temp[])
{
    if (left >= right)
        return;
    int mid = left + (right - left) / 2;
    mergeSort(a, left, mid, temp);
    mergeSort(a, mid + 1, right, temp);
    merge(a, left, right, mid, temp);
}
int main()
{
    int an[] = {8, 5, 4, 3, 1, 2, 6, 7};
    int temp[8];
    mergeSort(an, 0, 7, temp);
    return 0;
}
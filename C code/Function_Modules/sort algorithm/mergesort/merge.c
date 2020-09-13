#include <stdio.h>
#include <stdlib.h>

void merge(int array[], int tmp[], int left, int leftend, int rightend)
{
    int i = left, j = leftend + 1;
    int q = left;
    while (i <= leftend && j <= rightend)
        if (array[i] <= array[j])
            tmp[q++] = array[i++];
        else
            tmp[q++] = array[j++];
    while (i <= leftend)
        tmp[q++] = array[i++];
    while (j <= rightend)
        tmp[q++] = array[j++];
    for (i = left; i <= rightend; i++)
    {
        array[i] = tmp[i];
    }
}
void msort(int array[], int tmp[], int left, int right)
{
    if (left < right)
    {
        int mid = left + (right - left) / 2;
        msort(array, tmp, left, mid);
        msort(array, tmp, mid + 1, right);
        merge(array, tmp, left, mid, right);
    }
}
void mergesort(int array[], int left, int right)
{
    int *tmp = (int *)malloc(sizeof(int) * (right - left + 1));

    msort(array, tmp - left, left, right);

    free(tmp);
}
void print(int array[], int left, int right)
{
    for (int i = left; i <= right; i++)
        printf((i == right) ? "%d " : "%d\n", array[i]);
}
int main()
{
    int n;
    int array[101];
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &array[i]);
    }
    mergesort(array, 2, n - 1);
    print(array, 0, n - 1);
    return 0;
}
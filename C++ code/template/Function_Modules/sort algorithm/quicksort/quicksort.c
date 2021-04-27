#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
void swap(int *a, int *b)
{
    int p;
    p = *a;
    *a = *b;
    *b = p;
}
void quicksort(int array[], int left, int right)
{
    int i, j;
    int pivot;
    if (left < right)
    {
        i = left, j = right + 1;
        pivot = array[left];
        while (1)
        {
            while (array[++i] < pivot && i != right)
                ;
            while (array[--j] > pivot && j != left)
                ;
            if (i < j)
                swap(&array[i], &array[j]);
            else
                break;
        }
        swap(&array[left], &array[j]);
        quicksort(array, left, j - 1);
        quicksort(array, j + 1, right);
    }
}
void print(int array[], int left, int right)
{
    for (int i = left; i <= right; i++)
        printf((i == right) ? "%d " : "%d\n", array[i]);
}
int main()
{
    int array[101];
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
        scanf("%d", &array[i]);
    quicksort(array, 0, n - 1);
    print(array, 0, n - 1);
    return 0;
}
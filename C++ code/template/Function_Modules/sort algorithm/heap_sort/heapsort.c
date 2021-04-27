#include <stdio.h>
#include <stdlib.h>
//big heap
//ascendint sequence
void heapadjustdown(int a[], int pos, int n)
{
    int i = pos;
    int j = 2 * i + 1;
    int temp = a[i];
    for (; j < n;)
    {
        if (j + 1 < n && a[j + 1] > a[j])
            ++j;
        if (temp < a[j])
        {
            a[i] = a[j];
            i = j;
            j = 2 * i + 1;
        }
        else
            break;
    }
    a[i] = temp;
}
void makeheap(int a[], int n)
{
    for (int i = n / 2 - 1; i >= 0; i--)
    {
        heapadjustdown(a, i, n);
    }
}
void heapsort(int a[], int n)
{
    int temp;
    makeheap(a, n);
    for (int i = n - 1; i > 0; i--)
    {
        temp = a[i];
        a[i] = a[0];
        a[0] = temp;
        heapadjustdown(a, 0, i);
    }
}

void print(int array[], int n)
{
    for (int i = 0; i < n; i++)
    {
        printf("%d ", array[i]);
    }
    putchar('\n');
}
int main()
{
    int array[101];
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &array[i]);
    }
    heapsort(array, n);
    print(array, n);
    return 0;
}
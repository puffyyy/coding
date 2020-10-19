#include <stdio.h>
#include <stdlib.h>

void shell_sort(int array[], int n)
{
    int temp;
    for (int gap = n / 2; gap > 0; gap /= 2)
    {
        for (int i = gap; i < n; i++)
            for (int j = i - gap; j >= 0 && array[j] > array[j + gap]; j -= gap)
            {
                temp = array[j];
                array[j] = array[j + 1];
                array[j + 1] = temp;
            }
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
    shell_sort(array, n);
    print(array, n);
    return 0;
}
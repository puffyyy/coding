#include <stdio.h>
#include <stdlib.h>
void bubble_sort(int array[], int n)
{
    int flag = 1;
    int temp;
    for (int i = n - 1; flag == 1 && i > 0; i--)
    {
        flag = 0;
        for (int j = 0; j < i; j++)
        {
            if (array[j] > array[j + 1])
            {
                temp = array[j];
                array[j] = array[j + 1];
                array[j + 1] = temp;
                flag = 1;
            }
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
    bubble_sort(array, n);
    print(array, n);
    return 0;
}
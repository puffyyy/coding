#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int array[101];
void insert_sort(int* a)
{
    int current;
    for(int i=0;i<strlen(a)-1;i++)
    {
        current=a[i+1];
        int preindex=i;
        while (preindex>=0&&current<a[preindex])
        {
            a[preindex+1]=a[preindex];
            preindex--;
        }
        a[preindex+1]=current;
    }
    return;
}
int main()
{
    printf("Hello world!\n");
    return 0;
}

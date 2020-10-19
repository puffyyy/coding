#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define cmp_datatype int

int n;
int cmp(const void *a, const void *b) //返回值小于0 a 在 b前面
{
    cmp_datatype *c = (cmp_datatype *)a;
    cmp_datatype *d = (cmp_datatype *)b;
    return (*c - *d);
}

int main()
{
    scanf("%d", &n);

    printf("");
    return 0;
}
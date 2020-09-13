#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define cmp_datatype struct mem
struct mem
{
    int start, end;
} memory[120];
int n;
int cmp(const void *a, const void *b)
{
    cmp_datatype *c = (cmp_datatype *)a;
    cmp_datatype *d = (cmp_datatype *)b;
    return (c->start - d->start);
}

int main()
{
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
    {
        scanf("%d%d", &memory[i].start, &memory[i].end);
    }
    qsort(memory, n, sizeof(struct mem), cmp);
    for (int i = 0; i < n - 1;)
    {
        if (memory[i].end + 1 == memory[i + 1].start)
        {
            memory[i].end = memory[i + 1].end;
            n--;
            memcpy(memory + i + 1, memory + i + 2, (sizeof(struct mem) * (n - i - 1)));
        }
        else
            i++;
    }
    for (int i = 0; i < n; i++)
        printf("%d %d\n", memory[i].start, memory[i].end);
    return 0;
}
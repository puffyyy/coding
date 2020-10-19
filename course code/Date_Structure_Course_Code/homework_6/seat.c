#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define min(a, b) (a) < (b) ? (a) : (b)
struct student
{
    char name[24];
    int numb;
    int seat;
} stu[101];
int cmp(const void *a, const void *b)
{
    struct student *c, *d;
    c = (struct student *)a, d = (struct student *)b;
    if (0 == (c->seat) - (d->seat))
        return c->numb - d->numb;
    else
        return c->seat - d->seat;
}
int cmp2(const void *a, const void *b)
{
    struct student *c, *d;
    c = (struct student *)a, d = (struct student *)b;
    return c->numb - d->numb;
}
int main()
{
    FILE *in, *out;
    in = fopen("in.txt", "r");
    out = fopen("out.txt", "w");

    int n, q, k;
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
    {
        fscanf(in, "%d%s%d", &stu[i].numb, stu[i].name, &stu[i].seat);
    }
    qsort(stu + 1, n, sizeof(struct student), cmp);
    k = min(n, stu[n].seat);
    q = n;
    for (int i = 1, j = 1; i <= k && i <= stu[q].seat;)
    {
        if (i == stu[j].seat)
        {
            i++, j++;
        }
        else if (stu[j].seat == stu[j - 1].seat)
        {
            j++;
        }
        else
        {
            stu[q].seat = i;
            q--;
            i++;
        }
    }
    qsort(stu + 1, n, sizeof(struct student), cmp);
    q = stu[n].seat;
    for (int i = 2; i <= n; i++)
    {
        if (stu[i - 1].seat == stu[i].seat)
            stu[i].seat = ++q;
    }
    qsort(stu + 1, n, sizeof(struct student), cmp2);
    for (int i = 1; i <= n; i++)
        fprintf(out, "%d %s %d\n", stu[i].numb, stu[i].name, stu[i].seat);
    fclose(in);
    fclose(out);
    return 0;
}
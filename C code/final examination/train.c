#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define cmp_datatype struct address_
struct address_
{
    char s[21];
    int distance;
} address[51];
struct train_
{
    int num;
    char s[21];
    int distance;
} train[51];
int n, m;
int cnt;
int cmp(const void *a, const void *b) //降序
{
    cmp_datatype *c = (cmp_datatype *)a;
    cmp_datatype *d = (cmp_datatype *)b;
    return (d->distance - c->distance);
}
int find_dis(char s[])
{
    for (int i = 0; i < n; i++)
    {
        if (strcmp(s, address[i].s) == 0)
            return address[i].distance;
    }
    return -1;
}
int stacka[60];
int stackb[60];
int stackc[60];
int topa = -1;
int topb = -1;
int topc = -1;

void pusha(int item)
{
    cnt++;
    stacka[++topa] = item;
}
int popa()
{
    return stacka[topa--];
}
int isaempty()
{
    return topa == -1;
}
void pushb(int item)
{
    stackb[++topb] = item;
}
int popb()
{
    return stackb[topb--];
}
int isbempty()
{
    return topb == -1;
}
void pushc(int item)
{
    stackc[++topc] = item;
}
int popc()
{
    return stackc[topc--];
}
int iscempty()
{
    return topc == -1;
}
int search_far()
{
    int h = topb;
    int dis = -1;
    int pos = 0;
    for (int i = 0; i <= h; i++)
    {
        if (train[stackb[i]].distance >= dis)
        {
            dis = train[stackb[i]].distance;
            pos = i;
        }
    }
    return pos;
}
int check_M(int M)
{
    for (int i = 0; i < topa; i++)
    {
        if (train[stacka[i]].distance < train[stackb[M]].distance)
            return i;
    }
    return -1;
}
int main()
{
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
    {
        scanf("%s%d", address[i].s, &address[i].distance);
    }
    qsort(address, n, sizeof(struct address_), cmp);
    scanf("%d", &m);
    for (int i = 0; i < m; ++i)
    {
        scanf("%d%s", &train[i].num, train[i].s);
        train[i].distance = find_dis(train[i].s);
        pushb(m - i - 1);
    }
    while (topb != -1)
    {
        int M;
        M = search_far();
        while (M <= topb)
        {
            pusha(popb());
        }
        int flag = check_M(M);
        if (flag == -1)
            continue;
        else
        {
            pushc(popa()); // push M

            while (flag <= topa)
            {
                pushb(popa());
            }
            pusha(popc());
        }
    }
    for (int i = 0; i <= topa; i++)
        printf("%04d ", train[stacka[i]].num);
    putchar('\n');
    printf("%d", cnt);
    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#define MAXSIZE 10002
#define MAX(a, b) ((a) > (b) ? (a) : (b))
struct node
{
    int L, V;
};
typedef struct node Node;
typedef struct node *NodePtr;
Node data[MAXSIZE];
int Cmp(const void *a, const void *b)
{
    NodePtr c = (NodePtr)a;
    NodePtr d = (NodePtr)b;
    return d->V - c->V;
}
void Adjust(int i, int n)
{
    int j;
    Node tmp;
    tmp = data[i];
    j = 2 * i + 1;
    while (j < n)
    {
        if (j < n - 1 && data[j].L > data[j + 1].L)
            j++;
        if (tmp.L <= data[j].L)
            break;
        data[i] = data[j];
        i = j;
        j = i + i + 1;
    }
    data[i] = tmp;
}

void Heap(int n)
{
    int i;
    for (i = n / 2 - 1; i >= 0; i--)
        Adjust(i, n);
}
int main()
{
    int i, n, k;
    long long kmax = 0, lcur = 0;
    scanf("%d %d", &n, &k);
    for (i = 0; i < n; i++)
        scanf("%d %d", &data[i].L, &data[i].V);
    qsort(data, n, sizeof(Node), Cmp);
    k = (k > n ? n : k);
    for (i = 0; i < k; i++)
    {
        lcur += data[i].L;
        kmax = MAX(kmax, lcur * data[i].V);
    }
    Heap(k);
    for (i = k; i < n; i++)
    {
        if (data[i].L > data[0].L)
        {
            lcur += (data[i].L - data[0].L);
            data[0] = data[i];
            Adjust(0, k);
            kmax = MAX(kmax, lcur * data[i].V);
        }
    }
    printf("%lld\n", kmax);
    return 0;
}

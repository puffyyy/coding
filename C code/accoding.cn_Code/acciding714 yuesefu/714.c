#include <stdio.h>
#include <stdlib.h>
typedef struct cirlist
{
    int value;
    struct cirlist *next;
} list;
list *creat_circlelist(int n)
{
    list *head = (list *)malloc(sizeof(list));
    list *tail = head;
    for (int i = 0; i < n; i++)
    {
        list *p = (list *)malloc(sizeof(list));
        p->value = i;
        tail->next = p;
        tail = p;
    }
    tail->next = head;
    return head;
}
list *deletem(list *head, int m)
{
    list *p = head, *prior = p;
    while (head->next->next != head)
    {
        for (int i = 0; i < m; i++)
        {
            prior = p;
            p = p->next;
            if (p == head)
                i--;
        }
        prior->next = p->next;
        free(p);
        p = prior;
    }
}
int main()
{
    int n, m;
    scanf("%d%d", &n, &m);
    list *head = creat_circlelist(n);
    deletem(head, m);
    printf("%d", head->next->value + 1);
    return 0;
}
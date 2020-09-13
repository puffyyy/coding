#include <stdio.h>
#include <stdlib.h>
#define sizel (sizeof(struct line))
struct line
{
    int aft;
    float value;
    struct line *next;
    struct line *partner;
};
struct line *find_preNode(struct line *head, struct line *Node)
{
    if (!Node)
        return NULL;
    struct line *preNode = head;
    while (preNode)
    {
        if (preNode->next == Node)
            return preNode;
        preNode = preNode->next;
    }
    return NULL;
}

struct line *creatnode(int n)
{
    struct line *head1, *tail1, *p1, *head2, *tail2, *p2;
    head1 = (struct line *)malloc(sizel);
    tail1 = head1;
    head2 = (struct line *)malloc(sizel);
    tail2 = head2;
    head1->partner = head2;
    head2->partner = head1;
    int i;
    for (i = 0; i < n; i++)
    {
        p1 = (struct line *)malloc(sizel);
        p2 = (struct line *)malloc(sizel);
        scanf("%f %f", &p1->value, &p2->value);
        tail1->next = p1;
        tail1 = p1;
        p1->partner = p2;

        tail2->next = p2;
        tail2 = p2;
        p2->partner = p1;
    }
    tail1->next = NULL;
    tail2->next = NULL;
    return head1;
}
void insertnode(struct line *head, struct line *prea, struct line *a, struct line *preb, struct line *b) //插入b到a前
{
    preb->next = b->next;
    b->next = a;
    prea->next = b;
}
void insert_sort(struct line *head)
{

    struct line *q = head, *p = head->next,*prep=p;
    float current;
    if(p) p = p->next;
    while (p)
    {
        current = p->value; //当前要排序的值
        struct line *prepos=head,*posi = head->next;
        
        while (posi != p) //如果posi==p说明p前没有比current大的posi->value,p无需移动
            if (posi->value > current){
                insertnode(head,prepos, posi, prep, p);
                break;
            }
            else{
                posi = posi->next;
                prepos=prepos->next;
            }
        prep = p;
        p = p->next;
        
    }
}
void out_line(struct line *phead)
{
    if (phead == NULL)
        return;
    struct line *pNode = phead->next;
    while (pNode)
    {
        printf("%d ", (pNode->partner)->aft);
        pNode = pNode->next;
    }
    putchar('\n');
}
void loctnode(struct line *head)
{
    struct line *p = head->next;
    if(p){
        p->aft = 1;
        while (p->next)
        {
            p->next->aft = p->aft + 1;
            p = p->next;
        }
    }
}
int Destroyline(struct line *head)
{
    struct line *p;
    if (head == NULL)
        return 0;
    while (head)
    {
        p = head->next;
        free(head);
        head = p;
    }
    return -1;
}
int main()
{
    int n;
    while (~scanf("%d", &n))
    {
        struct line *headboy = creatnode(n);
        struct line *headgirl = headboy->partner;
        insert_sort(headboy);
        insert_sort(headgirl);
        loctnode(headboy);
        loctnode(headgirl);
        out_line(headboy);
        out_line(headgirl);
        Destroyline(headboy);
        Destroyline(headgirl);
    }
    return 0;
}
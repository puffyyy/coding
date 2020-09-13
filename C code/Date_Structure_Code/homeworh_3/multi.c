#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
typedef struct Node
{
    int coef; //coefficient
    int exp;  //exponent
    struct Node *next;
    struct Node *prior;
} node, *nodeptr;
struct abc
{
    int coef;
    int exp;
} date[2][10001];
nodeptr head ;
nodeptr tail ;
int myatoi(char *src)
{
    int s = 0, isMinus = 0;
    if (*src == '+' || *src == '-')
    {
        if (*src == '-')
        {
            isMinus = 1;
        }
        src++;
    }
    else
        while (*src != ' ' && *src >= '0' && *src <= '9')
        {
            s = s * 10 + *src - '0';
            src++;
        }
    return s * (isMinus ? -1 : 1);
}

nodeptr creat(nodeptr head,int a, int b)
{
    nodeptr p = (nodeptr)malloc(sizeof(node));
    p->coef = a;
    p->exp = b;
    tail->next = p;
    p->prior = tail;
    p->next = NULL;
    tail = p;
}
nodeptr delete_node(nodeptr p)
{
    nodeptr q = p->next;
    nodeptr s = p->prior;
    s->next = q;
    q->prior = p->prior;
    free(p);
    p = NULL;
    return s;
}
nodeptr insert_before_pre(nodeptr pre, nodeptr p)
{
    nodeptr q = p->prior;
    q->next = p->next;
    if(p->next!=NULL)
    p->next->prior = q; //delete p

    p->next = pre; //insert p
    pre->prior->next = p;
    p->prior = pre->prior;
    pre->prior = p;
    return q;
}
void insertsort(nodeptr head)
{
    if (head->next == NULL)
        return;
    nodeptr p = head->next;
    while (p->next != NULL)
    {
        nodeptr pre = head->next;
        p = p->next;

        while (pre != p)
        {
            if (pre->exp == p->exp)
            {
                pre->coef += p->coef;
                p = delete_node(p);
                break;
            }
            else if (pre->exp > p->exp)
            {
                p = insert_before_pre(pre, p);
                nodeptr temp=p; //swap(pre,p)
                p=pre;
                pre=temp;
                break;
            }
            else pre = pre->next;
        }
    }
}
void print(nodeptr head){
    nodeptr p=head;
    while(p->next!=NULL){
        p=p->next;
    }
    while(p!=head){
        printf("%d %d ",p->coef,p->exp);
        p=p->prior;
    }
}
int main()
{
    int l[2] = {0, 0};
    char line[20002];
    for (int i = 0; i < 2; i++) //read
    {
        gets(line);
        char *ch = line;
        line[strlen(line) + 1] = '~';
        int j = 0;
        while (*ch != '~')
        {
            int a, b;
            a = myatoi(ch);
            if (a != 0)
                ch += (int)log10(a) + 2;
            else
                ch += 2;
            b = myatoi(ch);
            if (b != 0)
                ch += (int)log10(b) + 2;
            else
                ch += 2;
            date[i][j].coef = a;
            date[i][j].exp = b;
            j++;
        }
        l[i] = j;
    }
    head = (nodeptr)malloc(sizeof(node));
    tail=head;
    for (int i = 0; i < l[0]; i++)//creat list
    {
        int a, b;
        for (int j = 0; j < l[1]; j++)
        {
            a = date[0][i].coef * date[1][j].coef;
            b = date[0][i].exp + date[1][j].exp;
            creat(head, a, b);
        }
    }
    insertsort(head);
    print(head);
    return 0;
}
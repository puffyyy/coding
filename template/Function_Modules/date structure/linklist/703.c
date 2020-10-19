#include<stdio.h>
#include<stdlib.h>
typedef struct node{
    int num;
    struct node *next;
}line;
line* creatnode(int n)
{
    line *head,*tail;
    head=malloc(sizeof (line));
    tail=head;
    for(int i=0;i<n;i++){
        line *p=malloc(sizeof(line));
        scanf("%d",&p->num);
        tail->next=p;
        tail=p;
    }
    tail->next=NULL;
    return head;
}
int delete_the_element_after(line* p){
    if(!p->next)return -1;
    line* q=p->next;
    p->next=q->next;
    free(q);
    return 1;

}
int deleterepeated(line* head)
{
    if(!head->next)return -1;
    line* p=head->next,*q=p->next;//p在后 q在前
    if(!q)return -1;
    while(q!=NULL){
        while(p->num==q->num){
            delete_the_element_after(p);
            q=p->next;
            if(!q) return 1;
        }
        p=q;
        q=q->next;
    }
    return 1;
}
int printnode(line* head)
{
    line* p=head->next;
    if(p==NULL)return -1;
    else while(p){
        printf("%d ",p->num);
        p=p->next;
    }
    putchar('\n');
    return 1;
}
int main()
{
    int n;
    while(~scanf("%d",&n)){
        line* head;
        head=creatnode(n);
        printnode(head);
        deleterepeated(head);
        printnode(head);
    }


    return 0;
}
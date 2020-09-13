#include<stdio.h>
#include<stdlib.h>
typedef struct Sqlist{
    int value;
    struct Sqlist *next;
}list;
list* creat_list()
{
    list* head=malloc(sizeof(struct Sqlist)),*tail;
    tail=head;
    int temp;
    while(~scanf("%d",&temp)){
        list* p=malloc(sizeof(struct Sqlist));
        p->value=temp;
        tail->next=p;
        tail=p;
    }
    tail->next=NULL;
    return head;
}
list* reversal_list(list* head,int k)//链表中每有k个数便将这k个数反转
{
    int i=k-1;
    if(head->next==NULL)return NULL;

    list *first=head,*end=first,*s,*r;
    r=end->next;//r记录end后的链表
    while(r!=NULL){
        if(end->next==NULL)break;
        if(first!=head)end=r,first=r;
        for(i=0;i<k-1;i++){
            
            if(end->next==NULL)break;
            end=end->next;
        }
        if(i==k-1){ 
            if(first==head){
                end=end->next;
                list *p,*q;
                s=first;
                p=first->next;
                s->next=end;
                q=p->next;
                s=p;
                list *end_next=end->next;
                while(q!=end_next){
                    r=q->next;
                    q->next=p;
                    p=q;
                    q=r;
                }
                if(q==NULL){s->next=NULL;return head;}
            }
            else {
                list *p,*q;
                
                p=first;
                s->next=end;
                q=p->next;
                s=p;
                list *end_next=end->next;
                while(q!=end_next){
                    r=q->next;
                    q->next=p;
                    p=q;
                    q=r;
                }
                if(q==NULL){first->next=NULL;return head;}
            }
        }
        else {
            s->next=first;
        }
        first=end;
        
    }
    
    return  head;
}
void print_list(list *head)
{
    list* p;
    if(head->next)p=head->next;
    while(p){
        printf("%d ",p->value);
        p=p->next;
    }
}
int main()
{
    int k;
    scanf("%d",&k);
    list* head=creat_list();
    if(k!=1)head=reversal_list(head,k);
    print_list(head);
    return 0;
}
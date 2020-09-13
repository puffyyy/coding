#include<stdio.h>
#include<stdlib.h>
typedef struct Node{
    int value;
    struct Node *next;    
}node;

int main()
{
    int n;
    scanf("%d",&n);
    int temp;
    node* head,* tail;
    head=(node*)malloc(sizeof(struct Node));
    tail=head;
    while(~scanf("%d",&temp)){
        node*p=(node*)malloc(sizeof(struct Node));
        p->value=temp;
        tail->next=p;
        tail=p;
    }
    tail->next=NULL;
    
    
    node* p,*q;
    int i;
    p=head;
    for(i=0;i<n;i++){
        p=p->next;
    }
    for(q=head;p->next!=NULL;p=p->next,q=q->next);
    
    printf("%d\n",q->next->value);
    q->next=q->next->next;
    q=head->next;
    
    if(q){while(q->next!=NULL){
        printf("%d",q->value);
        if(q->next!=NULL)printf("->");
        q=q->next;
    }
    printf("%d",q->value);}
    return 0;
}
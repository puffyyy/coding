#include<stdio.h>
#include<stdlib.h>
typedef struct Linklist{
    int value;
    struct Linklist *next;
}list,*listptr;
#define size_of_list (sizeof(list))

listptr creat_List(int n);//建立一个线性链表
int getlenth_list(listptr list);//求线性链表的长度
void insertFirst(listptr list ,int element);//在非空线性链表的第一个结点前插入一个数据信息为item的新结点
void insertNode(listptr list ,listptr p, int element);//在链表p结点后插入一个元素的结点
listptr searchNode(listptr list,int k);//在链表中查找倒数第k个元素
listptr find_preNode(listptr head,listptr Node);//查找前驱
void deleteNode(listptr list,listptr pre,listptr p);//删除节点
void destoryList(listptr list);//销毁链表
void printList();//打印链表
listptr creat_List_EOF();

int main()
{
    int n;
    scanf("%d",&n);
    //listptr list=creat_List(n);
    //list->value=getlenth_list(list);

    //printf("lenth of list:%d\n",list->value);
    //insertFirst(list,0);
    listptr list=creat_List_EOF();
    listptr node_d=searchNode(list,n);
    printf("%d\n",node_d->value);
    deleteNode(list,find_preNode(list->next,node_d),node_d);
    printList(list);
    return 0;
}
listptr creat_List(int n){
    listptr list,head,tail;
    list=(listptr)malloc(size_of_list);
    head=(listptr)malloc(size_of_list);
    list->next=head;
    tail=head;
    for(int i=0;i<n;i++){
        listptr p=(listptr)malloc(size_of_list);
        scanf("%d",&p->value);
        tail->next=p;
        tail=p;
    }
    tail->next=NULL;
    return list;
}
listptr creat_List_EOF(){
    listptr list,head,tail;
    list=(listptr)malloc(size_of_list);
    head=(listptr)malloc(size_of_list);
    list->next=head;
    tail=head;
    int temp;
    while(~scanf("%d",&temp)){
        listptr p=(listptr)malloc(size_of_list);
        p->value=temp;
        tail->next=p;
        tail=p;
    }
    tail->next=NULL;
    return list;
}
int getlenth_list(listptr list){
    listptr p=list->next->next;
    int lenth=0;
    for(;p;lenth++)p=p->next;
    return lenth;
}
void insertFirst(listptr list,int element){
    listptr p=(listptr)malloc(size_of_list);
    p->value=element;
    p->next=list->next->next;
    list->next->next=p;
}
void insertNode(listptr list,listptr p,int element){
    if(list==p)return;
    listptr q=malloc(size_of_list);
    q->value=element;
    q->next=p->next;
    p->next=q;
}
listptr searchNode(listptr list,int k){
    listptr p=list->next,q=p->next;
    int i;
    for(i=0;i<k;i++){
        p=p->next;
        if(p==NULL)return NULL;
    }
    for(;p->next!=NULL;p=p->next,q=q->next);
    return q;
}
listptr find_preNode(listptr head,listptr Node){
    if (!Node)
        return NULL;
    listptr preNode = head;
    while (preNode)
    {
        if (preNode->next == Node)
            return preNode;
        preNode = preNode->next;
    }
    return NULL;
}
void deleteNode(listptr list,listptr pre,listptr p){//删除p->指向的节点
    pre->next=p->next;
    //free(p);
}
void destoryList(listptr list){
    listptr p;
    if(list==NULL)return;
    while(list->next){
        p=list->next;
        free(list);
        list=p;
    }
    free(p);
}
void printList(listptr list){
    if(list==NULL)return ;
    listptr p=list->next->next;
    while(p){
        printf("%d",p->value);
        if(p->next)printf("->");
        p=p->next;
    }
    putchar('\n');
}


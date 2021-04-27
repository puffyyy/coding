#include<stdio.h>
#include<stdlib.h>

typedef struct appliciation{
    int num;
    int no;
    struct appliciation *next;
    struct appliciation *prior;
}app,*apptr;
app a[100001];
apptr head,tail;
int ans;
int cmpnum(const void *a,const void *b){
    apptr c=(apptr)a;
    apptr d=(apptr)b;
    return c->num-d->num;
}
void printlist(){
    apptr p=head->next;
    while(p!=tail){
        printf("%d:%2d ",p->no,p->num);
        p=p->next;
    }
    putchar('\n');
}
apptr swapapp(int q)
{
    apptr aft_q=a[q].next;
    apptr pre_q=a[q].prior;
    apptr ppre_q=pre_q->prior;
    ppre_q->next=&a[q];
    a[q].prior=ppre_q;
    a[q].next=pre_q;
    pre_q->prior=&a[q];
    pre_q->next=aft_q;
    if(aft_q)aft_q->prior=pre_q;
    a[q].num--;
    pre_q->num++;
}
void start(int q,int k){
    ans+=(a[q].num-1)/k;
    if(a[q].num!=1){
        swapapp(q);
        printlist();
    }
}
apptr creat(int n){
    int i;
    apptr head=malloc(sizeof(app));
    tail=malloc(sizeof(app));
    head->next=&a[0];
    a[0].prior=head;
    for(i=0;i<n-1;i++){
        a[i].next=&a[i+1];
    }
    a[i].next=tail;
    tail->prior=&a[i];
    tail->next=NULL;
    for(;i>0;i--){
        a[i].prior=&a[i-1];
    }
    return head;
}
void insert_sort(int n)
{
    int current,current1;
    apptr current3,current4;
    for(int i=0;i<n-1;i++)
    {
        current=a[i+1].no;
        current1=a[i+1].num;
        current3=a[i+1].next;
        current4=a[i+1].prior;
        int preindex=i;
        while (preindex>=0&&current<a[preindex].no)
        {
            a[preindex+1].no=a[preindex].no;
            a[preindex+1].num=a[preindex].num;
            a[preindex+1].next=a[preindex].next;
            a[preindex+1].prior=a[preindex].prior;
            preindex--;
        }
        a[preindex+1].no=current;
        a[preindex+1].num=current1;
        a[preindex+1].next=current3;
        a[preindex+1].prior=current4;
    }
    return;
}
int main()
{
    int n,m,k;
    while(~scanf("%d%d%d",&n,&m,&k)){
        ans=0;
        for(int i=0;i<n;i++){
            scanf("%d",&a[i].num);
            a[i].no=i;
        }
        
        qsort(a,n,sizeof(app),cmpnum);
        head=creat(n);
        printlist();
        insert_sort(n);
        for(int i=0;i<n;i++)
            if(a[i].num==1)head=a[i].prior;
        int query;
        for(int i=0;i<m;i++){
            scanf("%d",&query);
            start(query-1,k);//启动query号应用程序
        }
        printf("%d\n",ans+m);
    }
}

/*
3 5 1
3 2 1 
1 1 1 1 1
*/
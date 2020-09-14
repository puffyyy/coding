#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<math.h>
#define maxsize 21
struct node{
    int op;
    int pos;
    int n;
    char str[513];
    
};
struct Stack{
    struct node container[maxsize];
    int top;
};
static char text[513];
struct Stack* operated;
struct Stack* initStack(struct Stack* stack){
    stack=(struct Stack*)malloc(sizeof(struct Stack));
    stack->top=-1;
    return stack;
}
void destoryStack(struct Stack* stack){
    free(stack);
}
int isEmpty(struct Stack* stack){
    return stack->top==-1;
}
struct node pop(struct Stack* stack){
    if(isEmpty(stack))
        printf("empty! can not pop\n");
    struct node tmp;
    tmp.op=stack->container[stack->top].op;
    tmp.pos=stack->container[stack->top].pos;
    tmp.n=stack->container[stack->top].n;
    strcpy(tmp.str,stack->container[stack->top].str);

    (stack->top)--;
    return tmp;
}
void push(struct Stack* stack,struct node item){
    ++(stack->top);
    stack->container[stack->top].op=item.op;
    stack->container[stack->top].pos=item.pos;
    stack->container[stack->top].n=item.n;
    strcpy(stack->container[stack->top].str,item.str);
}
void deleteStr(struct node item){
    int n=item.n;
    int pos=item.pos;
    int len=strlen(text);
    char temp[101];
    //strcpy(text+pos,text+pos+n);
    sprintf(text+pos,text+pos+n);
    *(text+len-n)='\0';
}
void insertStr(struct node item){
    char str[513];
    strcpy(str,item.str);
    strcat(str,text+item.pos);
    strcpy(text+item.pos,str);
}

struct node readed(int op){
    struct node item;
    int pos;
    char str[513];
    item.op=op;
    scanf("%d",&pos);
    item.pos=pos;
    scanf("%s",str);
    strcpy(item.str,str);
    item.n=strlen(str);
    return item;
}
struct node read(int op){
    struct node item;
    item.op=op;
    switch (op)
    {
    case 1:
        scanf("%d",&item.pos);
        scanf("%s",item.str);
        item.n=strlen(item.str);
        break;
    case 2:
        scanf("%d",&item.pos);
        scanf("%d",&item.n);
        if(strlen(text)<item.n+item.pos)
            item.n=strlen(text)-item.pos;
        strncpy(item.str,text+item.pos,item.n);
        *(item.str+item.n)='\0';
    default:
        break;
    }
    return item;
}
void recover(){
    if(isEmpty(operated))return ;
    int op;
    struct node item;
    item=pop(operated);
    op=item.op;
    switch (op)
    {
    case 1:
        deleteStr(item);
        break;
    case 2:
        insertStr(item);
        break;
    default:
        break;
    }
}

int main(){
    int op,n;
    operated=initStack(operated);
    fgets(text,513,stdin);
    int lenth=strlen(text);
    text[lenth-1]='\0';

    scanf("%d",&n);
    for(int i=0;i<n;i++){
        scanf("%d",&op);
        struct node item;
        item=readed(op);
        push(operated,item);
    }
    //top+1 = n为op操作次数

    for(;;){
        struct node item;

        scanf("%d",&op);
        if(op==-1)
            break;
        else item=read(op);
        if(op==1||op==2)push(operated,item);
        if(op==1)
            insertStr(item);
        else if(op==2)
            deleteStr(item);
        else if(op==3)
            recover();
        //printf("%s\n",text);
    }
    printf("%s",text);
    destoryStack(operated);
    return 0;   
}
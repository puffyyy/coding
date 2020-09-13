#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<math.h>
typedef int datetype; 
typedef struct STACK_struct Stack;
struct STACK_struct{
    datetype* data;
    int Top;
    int MAXSIZE;
};
void init_Stack(Stack* stack,int initsize)
{
    stack->MAXSIZE=initsize;
    stack->Top=-1;
    stack->data=(datetype*)malloc(sizeof(datetype)*initsize);
}
void delete_stack(Stack* stack)
{
    free(stack->data);
}
int isEmpty(Stack stack)
{
    return stack.Top==-1;
}
int isFull(Stack stack)
{
    return stack.Top==stack.MAXSIZE-1;
}
int Push(Stack* stack,datetype item)
{
    if(stack->Top==stack->MAXSIZE-1){
        return -1;
    }
    else {
        stack->data[++stack->Top]=item;
    }
    return 1;
}
datetype Stack_top(Stack stack)
{
    if(stack.Top==-1){
        printf("The stack is empty.\n");
        return -2147483648;
    }
    return stack.data[stack.Top];
}
datetype Pop(Stack* stack)
{
    if(stack->Top==-1){
        return -2147483648;
    }
    return stack->data[stack->Top--];
}
int main(){
    Stack stack;
    init_Stack(&stack,100);
    int op;
    while(scanf("%d",&op)!=EOF){
        int temp;
        switch(op){
            case 1:   
            scanf("%d",&temp);
            if(Push(&stack,temp)==-1)printf("error ");
            break;
            case 0:
            temp=Pop(&stack);
            if(temp!=-2147483648)printf("%d ",temp);
            else printf("error ");
            break;
            default: break;
        }
        if(op==-1)break;
    }
    return 0;
}
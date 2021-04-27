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
void Push(Stack* stack,datetype item)
{
    if(stack->Top==stack->MAXSIZE-1){
        printf("The stack is full.\n");
        //exit(1);
        return;
    }
    else {
        stack->data[++stack->Top]=item;
    }
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
        printf("The stack is empty.\n");
        return -2147483648;
    }
    return stack->data[stack->Top--];
}
int main(){
    Stack stack;
    init_Stack(&stack,10);
    /*
      //test  
    Push(&stack,9);
    Push(&stack,10);
    printf("%d",Pop(&stack));
    */
    return 0;
}
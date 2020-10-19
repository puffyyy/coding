#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<math.h>
#define MAXSIZE 101
typedef int elemType;
elemType QUEUE[MAXSIZE];
int Front,Rear,Count;
void initQueue(){
    Front=0;
    Rear=MAXSIZE-1;
    Count=0;
}
int isEmpty(){
    return Count==0;
}
int isFull(){
    return Count==MAXSIZE;
}
void enQueue(elemType queue[],elemType item){
    if(isFull())
        printf("full queue.\n");
    else {
        Rear=(Rear+1)%MAXSIZE;
        queue[Rear]=item;
        Count++;
    }
}
elemType deQueue(elemType queue[]){
    elemType e;
    if(isEmpty())
        printf("empty queue!\n");
    else {
        e=queue[Front];
        --Count;
        Front=(Front+1)%MAXSIZE;
        return e;
    }
}

int main(){
    
    return 0;
}
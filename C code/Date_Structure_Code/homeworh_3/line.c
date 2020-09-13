#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define max(a,b) (a)>(b)?(a):(b)
typedef struct Node
{
    int x1,x2,y1,y2;
    struct Node *next;
} node, *nodeptr;
node line[10];
int main(){
    int n,ret=-1,x,y;
    scanf("%d",&n);
    for(int i=0;i<n;i++){//init
        scanf("%d%d%d%d",&line[i].x1,&line[i].y1,&line[i].x2,&line[i].y2);
        line[i].next=NULL;
    }
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            if(line[i].x2==line[j].x1&&line[i].y2==line[j].y1)line[i].next=&line[j];
        }
    }
    for(int i=0;i<n;i++){
        int len=1;
        nodeptr temp=&line[i];
        while(temp->next!=NULL){
            temp=temp->next;
            len++;
        }
        if(len>ret){
            ret=len;
            x=line[i].x1;
            y=line[i].y1;
        }
    }
    printf("%d %d %d",ret,x,y);
    return 0;
}
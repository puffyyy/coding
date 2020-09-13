#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<math.h>
#define MAXSIZE 201
#define THRESHOLD 7
#define MAXSVR 5
#define MINSVR 3
typedef struct {
    int id;
    int wtime;
}CustType;
int Winnum=MINSVR;
CustType Cqueue[MAXSIZE];
static int Cfront=0;
static int Crear=-1;
static int Cnum=0;
void updateCustqueue();
void enCustqueue(CustType c);
CustType deCustqueue();
int getCustqueue();
int isFull();
int isEmpty();
void arriveCust();
int service();


int main(){
    int clock,simulationtime;
    scanf("%d",&simulationtime);
    for(clock=1;;++clock){
        updateCustqueue();
        if(clock<=simulationtime){
            arriveCust();
        }
        if(service()==0&&clock>simulationtime){
            break;
        }
    }
    return 0;
}




void updateCustqueue(){
    int i;
    for(i=0;i<Cnum;i++)
        Cqueue[(Cfront+i)%MAXSIZE].wtime++;
}
void enCustqueue(CustType c){
    if(isFull())printf("FULL queue!\n");
    else {
        Crear=(Crear+1)%MAXSIZE;
        Cqueue[Crear]=c;
        Cnum++;
    }
}
CustType deCustqueue(){
    CustType c;
    if(isEmpty())printf("empty queue\n");
    else {
        c=Cqueue[Cfront];
        Cnum--;
        Cfront=(Cfront+1)%MAXSIZE;
        return c;
    }
}
int getCustqueue(){
    return Cnum;
}
int isFull(){
    return Cnum==MAXSIZE;
}
int isEmpty(){
    return Cnum==0;
}
void arriveCust(){
    int i,n;
    static int count = 1;
    CustType c;
    scanf("%d",&n);
    for(i=0;i<n;i++){
        c.id=count++;
        c.wtime=0;
        enCustqueue(c);
    }
    while((getCustqueue()/Winnum)>=THRESHOLD&&Winnum<MAXSVR)
        Winnum++;
}
int service(){
    int i;
    CustType c;
    for(i=0;i<Winnum;++i){
        if(isEmpty())return 0;
        else {
            c=deCustqueue();
            printf("%d : %d\n",c.id,c.wtime);
        }
    }
    if((getCustqueue()/Winnum)<THRESHOLD&&Winnum>MINSVR)
    --Winnum;
    return 1;
}
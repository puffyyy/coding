#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
typedef int elemType;
struct node
{
    elemType data;
    struct node *link;
};
typedef struct node QNode;
typedef struct node *QNodeptr;
QNodeptr Front, Rear;
void initQueue()
{
    Front = NULL;
    Rear = NULL;
}
int isEmpty()
{
    return Front == NULL;
}
void enQueue(elemType item)
{
    QNodeptr p;
    if ((p = (QNodeptr)malloc(sizeof(QNode))) == NULL)
        printf("No memory");
    p->data = item;
    p->link = NULL;
    if (Front == NULL)
        Front = p;
    else
        Rear->link = p;
    Rear = p;
}
elemType deQueue()
{
    if (Front == NULL)
        printf("Empty queue!\n");
    else
    {
        QNodeptr p = Front;
        Front = Front->link;
        elemType item = p->data;
        free(p);
        return item;
    }
}
void destoryQueue()
{
    while (Front != NULL)
    {
        Rear = Front->link;
        free(Front);
        Front = Rear;
    }
}
int main()
{

    return 0;
}
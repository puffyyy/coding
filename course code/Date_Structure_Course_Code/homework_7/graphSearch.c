#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define MAXSIZE 101
int rear = MAXSIZE - 1, front = 0, count = 0;
int queue[MAXSIZE];
void enqueue(int item)
{
    rear = (rear + 1) % MAXSIZE;
    queue[rear] = item;
    ++count;
}
int isempty()
{
    return count == 0;
}
int dequeue()
{
    if (count == 0)
        return -1;
    int tmp = queue[front];
    front = (front + 1) % MAXSIZE;
    --count;
    return tmp;
}

struct edgeNode
{
    int end;
    struct edgeNode *next;
};
struct vertex
{
    int data;
    int vstate;
    struct edgeNode *next;
} adjList[MAXSIZE];
struct edgeNode *insertEdge(struct edgeNode *head, int end)
{
    struct edgeNode *e, *p = head, *q = head;
    e = (struct edgeNode *)malloc(sizeof(struct edgeNode));
    e->end = end, e->next = NULL;
    if (head == NULL)
        return head = e;
    else
    {
        for (; p != NULL && end >= p->end; p = p->next)
            q = p;
    }
    if (p == head)
    {
        e->next = head;
        head = e;
    }
    else
    {
        e->next = q->next;
        q->next = e;
    }

    return head;
}
void creatEdges(int numver, int numedge)
{
    int start, end;
    for (int i = 0; i < numver; i++)
    {
        adjList[i].data = i;
        adjList[i].vstate = 0;
        adjList[i].next = NULL;
    }
    for (int i = 0; i < numedge; i++)
    {
        scanf("%d%d", &start, &end);
        adjList[start].next = insertEdge(adjList[start].next, end);
        adjList[end].next = insertEdge(adjList[end].next, start);
    }
}
void deleteVertex()
{
    int x;
    scanf("%d", &x);
    adjList[x].next = NULL;
    adjList[x].vstate = -1;
}
void DFS(int start)
{
    struct edgeNode *p;
    adjList[start].vstate = 1;
    printf("%d ", start);
    for (p = adjList[start].next; p != NULL; p = p->next)
    {
        if (0 == adjList[p->end].vstate)
            DFS(p->end);
    }
}
void BFS(int start)
{
    int v;
    struct edgeNode *p;
    printf("%d ", start);
    adjList[start].vstate = 1;
    enqueue(start);
    while (!isempty())
    {
        v = dequeue();
        for (p = adjList[v].next; p != NULL; p = p->next)
        {
            if (0 == adjList[p->end].vstate)
            {
                printf("%d ", p->end);
                enqueue(p->end);
                adjList[p->end].vstate = 1;
            }
        }
    }
}
void DFStravel(int numver)
{
    for (int i = 0; i < numver; i++)
    {
        if (adjList[i].vstate == 1)
            adjList[i].vstate = 0;
    }
    for (int i = 0; i < numver; i++)
    {
        if (adjList[i].vstate == 0)
            DFS(i);
    }
    putchar('\n');
}
void BFStravel(int numver)
{
    for (int i = 0; i < numver; i++)
    {
        if (adjList[i].vstate == 1)
            adjList[i].vstate = 0;
    }
    for (int i = 0; i < numver; i++)
    {
        if (adjList[i].vstate == 0)
            BFS(i);
    }
    putchar('\n');
}
void print(int numver)
{
    DFStravel(numver);
    BFStravel(numver);
}
int main()
{
    int numver, numedge;
    scanf("%d%d", &numver, &numedge);
    creatEdges(numver, numedge);
    print(numver);
    deleteVertex();
    print(numver);
    return 0;
}
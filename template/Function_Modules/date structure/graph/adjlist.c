//adjacency list
#include <stdio.h>
#include <stdlib.h>
#define MAXVER 10
struct edgeNode
{
    int ver_no, weight;
    struct edgeNode *link;
};
struct VERTEX
{
    int data;
    struct edgeNode *link;
} adjList[MAXVER];
struct edgeNode *insertEdge(struct edgeNode *head, int end, int weight)
{
    struct edgeNode *e, *p;
    e = (struct edgeNode *)malloc(sizeof(struct edgeNode));
    e->ver_no = end;
    e->weight = weight;
    e->link = NULL;
    if (head == NULL)
        return head = e;
    else
    {
        for (p = head; p->link != NULL; p = p->link)
            ;
    }
    p->link = e;
    return head;
}
void creatGraph()
{
    int i, numVertexes, numEdges, s, e, w;
    scanf("%d%d", &numVertexes, &numEdges);
    for (i = 0; i < numVertexes; i++)
    {
        scanf("%d", adjList[i].data);
        adjList[i].link = NULL;
    }
    for (i = 0; i < numEdges; i++)
    {
        scanf("%d%d%d", &s, &e, &w);
        insertEdge(adjList[s].link, e, w);
        //insertEdge(adjList[e].link, s, w);//无向图
    }
}
int main()
{

    return 0;
}
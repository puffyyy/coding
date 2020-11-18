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
    int inorder, outorder;
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
void creatGraph(int numVertexes, int numEdges)
{
    int i, s, e, w;

    for (i = 0; i < numVertexes; i++)
    {
        scanf("%d", adjList[i].data);
        adjList[i].inorder = adjList[i].outorder = 0;
        adjList[i].link = NULL;
    }
    for (i = 0; i < numEdges; i++)
    {
        scanf("%d%d%d", &s, &e, &w);
        insertEdge(adjList[s].link, e, w);
        adjList[s].outorder++;
        adjList[e].inorder++;
        //insertEdge(adjList[e].link, s, w);//无向图
    }
}
void topolpgy(int numVertexes)
{
    int inorder[MAXVER], visit[MAXVER];
    for (int i = 0; i < numVertexes; i++)
    {
        inorder[i] = adjList[i].inorder;
        visit[i] = 0;
    }
    for (int i = 0; i < numVertexes; i++)
    {
        for (int i = 0; i < numVertexes; i++)
            if (!visit[i] && inorder[i] == 0)
            {
                struct edgeNode *p = adjList[i].link;
                while (p != NULL)
                {
                    inorder[p->ver_no]--;
                    p = p->link;
                }
                printf("%d", i);
                visit[i] = 1;
                break;
            }
    }
}
int main()
{
    int numVertexes, numEdges;
    scanf("%d%d", &numVertexes, &numEdges);
    creatGraph(numVertexes, numEdges);
    topolpgy(numVertexes);
    return 0;
}
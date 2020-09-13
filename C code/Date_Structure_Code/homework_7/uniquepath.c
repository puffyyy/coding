#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define MAXVER 45
struct edgeNode
{
    int id;
    int end;
    struct edgeNode *next;
};
struct vertex
{
    int data;
    int vstate;
    struct edgeNode *next;
} adjList[MAXVER];
int path[MAXVER];

struct edgeNode *insertEdge(struct edgeNode *head, int id, int end)
{
    struct edgeNode *e, *p = head, *q = head;
    e = (struct edgeNode *)malloc(sizeof(struct edgeNode));
    e->id = id, e->end = end, e->next = NULL;
    if (head == NULL)
        return head = e;
    else
    {
        for (; p != NULL && id > p->id; p = p->next)
            q = p;
    }
    e->next = q->next;
    q->next = e;
    return head;
}
void printpath(int n)
{
    for (int i = 0; i < n; i++)
        printf("%d ", path[i]);
    putchar('\n');
}
void dfs(int v, int terminal, int level)
{
    adjList[v].vstate = 1;
    if (v == terminal)
    {
        printpath(level);
        return;
    }
    struct edgeNode *p;
    for (p = adjList[v].next; p != NULL; p = p->next)
    {
        if (!adjList[p->end].vstate)
        {
            path[level] = p->id;
            adjList[p->end].vstate = 1;
            dfs(p->end, terminal, level + 1);
            adjList[p->end].vstate = 0;
        }
    }
}
int main()
{
    int n, e;
    int id, start, end;
    scanf("%d%d", &n, &e);
    for (int i = 0; i < n; i++)
    {
        adjList[i].data = i;
        adjList[i].vstate = 0;
        adjList[i].next = NULL;
    }
    for (int i = 0; i < e; i++)
    {
        scanf("%d%d%d", &id, &start, &end);
        adjList[start].next = insertEdge(adjList[start].next, id, end);
        adjList[end].next = insertEdge(adjList[end].next, id, start);
    }
    dfs(0, n - 1, 0);
    return 0;
}
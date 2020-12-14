/* 
 Author: 杨东霖
 Result: AC	Submission_id: 2995683
 Created at: Sat Nov 14 2020 16:29:00 GMT+0800 (China Standard Time)
 Problem_id: 3655	Time: 113	Memory: 11204
*/

#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include <stack>
#include <queue>
#include <set>
using namespace std;
typedef long long ll;
const int MS = 1e6 + 5;
#define MAXVER MS
int visit[MAXVER];
struct edgeNode
{
    int ver_no, weight;
    struct edgeNode *link;
};
struct VERTEX
{
    int in;
    int out;
    struct edgeNode *link;
} adjList[MAXVER];
struct edgeNode *insertEdge(struct edgeNode **head, int end, int weight)
{
    struct edgeNode *e, *p;
    e = (struct edgeNode *)malloc(sizeof(struct edgeNode));
    e->ver_no = end;
    e->weight = weight;
    e->link = NULL;
    if (*head == NULL)
        return *head = e;
    else
    {
        p = (*head)->link;
        (*head)->link = e;
        e->link = p;
    }
    return *head;
}
void creatGraph(int numVertexes, int numEdges)
{
    int i, s, e, w;
    for (i = 0; i < numVertexes; i++)
    {
        adjList[i].in = adjList[i].out = 0, adjList[i].link = NULL;
    }
    for (i = 0; i < numEdges; i++)
    {
        scanf("%d%d", &s, &e);
        insertEdge(&adjList[s].link, e, 1);
        adjList[s].out++;
        adjList[e].in++;
    }
}
void visit_i(int i)
{
    printf("%d ", i);
    visit[i] = 1;
}
void bfs_visit(int source)
{
    queue<int> que;
    que.push(source);
    int u;
    struct edgeNode *p;
    while (!que.empty())
    {
        u = que.front(), que.pop();
        visit_i(u);
        p = adjList[u].link;
        while (p)
        {
            adjList[p->ver_no].in--;
            if (visit[p->ver_no] == 0 && adjList[p->ver_no].in == 0)
            {
                visit[p->ver_no] = 1;
                que.push(p->ver_no);
            }
            p = p->link;
        }
    }
}
void bfs(int n)
{
    for (int i = 0; i < n; i++)
        if (adjList[i].in == 0 && visit[i] == 0)
        {
            bfs_visit(i);
        }
}
int main()
{
    //ios::sync_with_stdio(false);
    //cin.tie(nullptr);
    int n, m;
    scanf("%d%d", &n, &m);
    creatGraph(n, m);
    bfs(n);

    return 0;
}
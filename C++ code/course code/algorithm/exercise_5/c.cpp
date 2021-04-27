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
const int INF = 0x3fffffff;
const int MS = 900 + 5;
#define MAXVER MS
int visit[MS];
int pre[MS];
struct edgeNode *dis[MS];
int a[31][31];
int flow = 0;
struct edgeNode
{
    int ver_no, weight;
    struct edgeNode *link;
};
struct VERTEX
{
    // int id;
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
void creatGraph(int n, int m, int source, int terminal)
{
    for (int i = 0; i <= terminal; i++)
        adjList[i].link = NULL;

    for (int i = 1; i <= m; i++)     //m hang
        for (int j = 1; j <= n; j++) // n lie
        {
            if (((i + j) & 1) == 0) //black
            {
                insertEdge(&adjList[0].link, (i - 1) * n + j, a[i][j]);
            }
            else
            {
                if (i != 1)
                    insertEdge(&adjList[(i - 2) * n + j].link, (i - 1) * n + j, INF);
                if (i != m)
                    insertEdge(&adjList[i * n + j].link, (i - 1) * n + j, INF);
                if (j != 1)
                    insertEdge(&adjList[(i - 1) * n + j - 1].link, (i - 1) * n + j, INF);
                if (j != n)
                    insertEdge(&adjList[(i - 1) * n + j + 1].link, (i - 1) * n + j, INF);
                insertEdge(&adjList[(i - 1) * n + j].link, terminal, a[i][j]);
            }
        }
    struct edgeNode *p;
    for (int i = 0; i <= terminal; i++) //m hang
    {
        p = adjList[i].link;
        while (p)
        {
            insertEdge(&adjList[p->ver_no].link, i, 0);
            p = p->link;
        }
    }
}
int bfs(int source, int terminal)
{
    queue<int> que;
    memset(visit, 0, sizeof(visit));
    memset(pre, 0, sizeof(pre));
    visit[source] = 1;
    pre[source] = -1;
    dis[source] = 0;
    que.push(source);
    int u;
    while (!que.empty())
    {
        u = que.front(), que.pop();
        if (u == terminal)
            return 1;
        struct edgeNode *p = adjList[u].link;
        while (p)
        {
            if (visit[p->ver_no] == 0 && p->weight != 0)
            {
                dis[p->ver_no] = p;
                pre[p->ver_no] = u;
                visit[p->ver_no] = 1;
                que.push(p->ver_no);
            }
            p = p->link;
        }
    }
    return 0;
}
void maxmflow(int s, int t)
{
    while (bfs(s, t))
    {
        long long minadd = INF;
        int next = t;
        while (next != s)
        {
            if (minadd > dis[next]->weight)
                minadd = dis[next]->weight;
            next = pre[next];
        }
        next = t;
        struct edgeNode *p;
        while (next != s)
        {
            dis[next]->weight -= minadd;
            int u;
            u = pre[next];
            p = adjList[next].link;
            while (p)
            {
                if (p->ver_no == u)
                    break;
                p = p->link;
            }
            p->weight += minadd;
            next = pre[next];
        }
        flow += minadd;
    }
}
int main()
{
    int m, n;
    int sum = 0;
    scanf("%d%d", &m, &n);
    for (int i = 1; i <= m; i++)     //m hang
        for (int j = 1; j <= n; j++) // n lie
        {
            scanf("%d", &a[i][j]);
            sum += a[i][j];
        }
    int source = 0, terminal = n * m + 1;
    creatGraph(n, m, source, terminal);
    maxmflow(source, terminal);
    printf("%d", sum - flow);
    return 0;
}
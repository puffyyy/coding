#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#define MAXNUM 512
#define MAXLEN 16
#define INFINITY 32767
FILE *in;
struct station
{
    char name[MAXLEN];
    int ischange;
} vertex[MAXNUM];
struct weight
{
    int weight;
    int no;
} adjmatrix[MAXNUM][MAXNUM];
int path[MAXNUM], minweight[MAXNUM];
int vnum = 0;

void initGraph(int n)
{
    int i, j, k;
    int line, linevernum;
    for (i = 0; i < MAXNUM; i++)
        for (j = 0; j < MAXNUM; j++)
            adjmatrix[i][j].weight = ((i == j) ? 0 : INFINITY);
    for (i = 0; i < n; i++) //n条地铁线路
    {
        char name[MAXLEN];
        int ischange, pre;
        fscanf(in, "%d%d", &line, &linevernum);
        for (j = 0; j < linevernum; j++) //在这条地铁线路中有linevernum个站
        {
            fscanf(in, "%s%d", name, &ischange);
            //printf("%s\n", name);
            if (j == 0)
                pre = vnum;
            for (k = 0; k < vnum; k++) //查找是否已经存在站点
            {
                if (strcmp(name, vertex[k].name) == 0)
                    break;
            }
            if (strcmp(name, vertex[k].name) == 0) //如果存在
            {
                adjmatrix[k][pre].weight = 1;
                adjmatrix[k][pre].no = line;
                adjmatrix[pre][k].weight = 1;
                adjmatrix[pre][k].no = line;
                pre = k;
            }
            else
            {
                //建立新顶点
                strcpy(vertex[vnum].name, name);
                vertex[vnum].ischange = ischange;
                if (vnum != pre) //当前线路第一个节点
                {
                    adjmatrix[vnum][pre].weight = 1;
                    adjmatrix[vnum][pre].no = line;
                    adjmatrix[pre][vnum].weight = 1;
                    adjmatrix[pre][vnum].no = line;
                    pre = vnum;
                }
                vnum++;
            }
        }
    }
}
void printMatrix()
{
    for (int i = 0; i < vnum; i++)
    {
        for (int j = 0; j < vnum; j++)
            printf("%6d ", adjmatrix[i][j].weight);
        putchar('\n');
    }
}
void dijkstra(int source)
{
    char visit[vnum];
    for (int i = 0; i < vnum; i++)
    {
        minweight[i] = adjmatrix[source][i].weight;
        visit[i] = 0;
        path[i] = source;
    }
    minweight[source] = 0;
    visit[source] = 1;
    for (int i = 0; i < vnum - 1; i++)
    {
        int v, min = INFINITY;
        for (int j = 0; j < vnum; j++)
        {
            if (visit[j] != 1 && min > minweight[j])
            {
                min = minweight[j];
                v = j;
            }
        }
        visit[v] = 1;
        for (int j = 0; j < vnum; j++)
        {
            if (visit[j] != 1 && adjmatrix[v][j].weight != INFINITY && minweight[j] > (adjmatrix[v][j].weight + min))
            {
                minweight[j] = min + adjmatrix[v][j].weight;
                path[j] = v;
            }
        }
    }
}
int searchVertex(char *s)
{
    int k;
    for (k = 0; k < vnum; k++) //查找是否已经存在站点
    {
        if (strcmp(s, vertex[k].name) == 0)
            return k;
    }
    return -1;
}
void printPath(int start, int k)
{
    if (k == start)
        printf("%s", vertex[k].name);
    else
    {
        printPath(start, path[k]);
        printf("->%s", vertex[k].name);
    }
}

int top = -1;
int stack[MAXNUM];
int isempty()
{
    return top == -1;
}
int pop()
{
    return stack[top--];
}
void push(int x)
{
    stack[++top] = x;
}
void print(int start, int end)
{
    int v = end;

    while (path[v] != start)
    {
        push(v);
        v = path[v];
    }
    int prev, line, preline = -1, cnt = 1;
    prev = v;
    preline = adjmatrix[start][prev].no;
    printf("%s", vertex[start].name);
    while (top > 0)
    {
        v = pop();
        line = adjmatrix[prev][v].no;

        if (preline != line)
        {
            printf("-%d(%d)-%s", preline, cnt, vertex[prev].name);
            cnt = 1;
        }
        else if (preline == line)
            cnt++;
        prev = v;
        preline = line;
    }
    line = adjmatrix[prev][end].no;
    if (line == preline)
        printf("-%d(%d)-%s", preline, ++cnt, vertex[end].name);
    else
    {
        printf("-%d(%d)-%s", preline, cnt, vertex[prev].name);
        cnt = 1;
        printf("-%d(%d)-%s", line, cnt, vertex[end].name);
    }
}
int main()
{
    in = fopen("bgstations.txt", "r");
    int linenum, start, end;
    char source[MAXLEN], terminal[MAXLEN];
    fscanf(in, "%d", &linenum);
    initGraph(linenum);
    scanf("%s%s", source, terminal);
    // printMatrix();
    start = searchVertex(source);
    end = searchVertex(terminal);
    dijkstra(start);
    //printPath(start, end);
    //putchar('\n');
    print(start, end);
    return 0;
}
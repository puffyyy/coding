#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define max(a, b) ((a) > (b) ? (a) : (b))
#define MAXD 3
struct Node
{
    int val;
    int height;
    struct Node *next[MAXD];
} * tree;
typedef struct Node node;
node *maxdNode[1001];
int maxd = 0;
node *creatnode(int val, int l, int m, int r)
{
    node *p = (node *)malloc(sizeof(node));
    p->val = val;
    if (tree == NULL)
    {
        tree = p;
        p->height = 0;
    }
    if (l == 0)
        p->next[0] = NULL;
    else
    {
        p->next[0] = creatnode(l, 0, 0, 0);
        p->next[0]->height = p->height + 1;
    }
    if (m == 0)
        p->next[1] = NULL;
    else
    {
        p->next[1] = creatnode(m, 0, 0, 0);
        p->next[1]->height = p->height + 1;
    }
    if (r == 0)
        p->next[2] = NULL;
    else
    {
        p->next[2] = creatnode(r, 0, 0, 0);
        p->next[2]->height = p->height + 1;
    }
    return p;
}
node *searchnode(int val, node *root)
{
    node *p = root;
    node *stack[1001];
    int top = -1;
    while (p != NULL)
    {
        stack[++top] = root;
        while (top != -1)
        {
            p = stack[top--];
            if (p->val == val)
                return p;
            if (p->next[2] != NULL)
                stack[++top] = p->next[2];
            if (p->next[1] != NULL)
                stack[++top] = p->next[1];
            if (p->next[0] != NULL)
                stack[++top] = p->next[0];
        }
    }
    return NULL;
}
int branch(node *root, int n)
{
    if (n == 3)
        if (root->next[0] != NULL && root->next[1] != NULL && root->next[2] != NULL)
            return 3;
        else
            return -1;
    if (n == 2)
        if ((root->next[0] != NULL && root->next[1] != NULL) || (root->next[1] != NULL && root->next[2] != NULL) || (root->next[0] != NULL && root->next[2] != NULL))
            return 2;
        else
            return -1;
    if (n == 1)
        if (root->next[0] != NULL || root->next[1] != NULL || root->next[2] != NULL)
            return 1;
        else
            return -1;
}
int store(node *p)
{
    static int i = 0;
    if (branch(p, maxd) == maxd)
        maxdNode[i++] = p;
    return i;
}
int cnt(node *root, node *sea)
{
    int i = 0;
    node *p = root;
    node *stack[1001];
    int top = -1;
    if (p != NULL)
    {
        stack[++top] = root;
        while (top != -1)
        {
            p = stack[top--];
            ++i;
            if (p == sea)
                return i;
            if (p->next[2] != NULL)
                stack[++top] = p->next[2];
            if (p->next[1] != NULL)
                stack[++top] = p->next[1];
            if (p->next[0] != NULL)
                stack[++top] = p->next[0];
        }
    }
    return -1;
}
node *preorder(node *root, int (*visit)(node *))
{
    node *p = root;
    node *stack[1001];
    int top = -1;
    if (p != NULL)
    {
        stack[++top] = root;
        while (top != -1)
        {
            p = stack[top--];
            (*visit)(p);

            if (p->next[2] != NULL)
                stack[++top] = p->next[2];
            if (p->next[1] != NULL)
                stack[++top] = p->next[1];
            if (p->next[0] != NULL)
                stack[++top] = p->next[0];
        }
    }
    return NULL;
}
node *updatenode(node *p, int l, int m, int r)
{
    if (l == 0)
        p->next[0] = NULL;
    else
    {
        p->next[0] = creatnode(l, 0, 0, 0);
        p->next[0]->height = p->height + 1;
    }
    if (m == 0)
        p->next[1] = NULL;
    else
    {
        p->next[1] = creatnode(m, 0, 0, 0);
        p->next[1]->height = p->height + 1;
    }
    if (r == 0)
        p->next[2] = NULL;
    else
    {
        p->next[2] = creatnode(r, 0, 0, 0);
        p->next[2]->height = p->height + 1;
    }
}
int main()
{
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
    {
        int val, next[3];
        node *tmp;
        scanf("%d%d%d%d", &val, &next[0], &next[1], &next[2]);
        for (int j = 0; maxd != 3 && j < 3; j++)
            if (next[j] != 0)
                maxd = max(maxd, j + 1);
        if ((tmp = searchnode(val, tree)) == NULL)
            creatnode(val, next[0], next[1], next[2]);
        else
            updatenode(tmp, next[0], next[1], next[2]);
    }
    int (*sto)(node *) = store;
    preorder(tree, sto);
    int maxheight = 0;
    for (int i = 0; maxdNode[i] != NULL; i++)
    {
        maxheight = max(maxheight, maxdNode[i]->height);
    }
    for (int i = 0; maxdNode[i] != NULL; i++)
    {
        if (maxdNode[i]->height == maxheight)
            printf("%d %d\n", maxdNode[i]->val, cnt(tree, maxdNode[i]));
    }
    return 0;
}
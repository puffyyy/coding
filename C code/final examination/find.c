#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX(a, b) ((a) > (b) ? (a) : (b))

FILE *fin;
int n;
char stringf[21];
struct File
{
    char name[21];
    char parentname[21];
    int date;
    int flag;
    int layer;
    int pos;
    struct File *parent;
    int degree;
    struct File *next[101];
} * root, *allfind[10010];
int cmp(const void *a, const void *b) //返回值小于0 a 在 b前面 a-b
{
    struct File **c = (struct File **)a;
    struct File **d = (struct File **)b;
    if ((*c)->date == (*d)->date)
    {
        if ((*c)->layer == (*d)->layer)
        {
            return ((*c)->pos - (*d)->pos);
        }
        else
            return ((*c)->layer - (*d)->layer);
    }
    else
        return ((*d)->date - (*c)->date);
}
void searchParentName(struct File *tree, char s[], struct File **parent)
{
    if (tree != NULL)
        if (strcmp(tree->name, s) == 0)
        {
            *parent = tree;
            return;
        }

    for (int i = 0; i < tree->degree; i++)
    {
        if (tree->next[i] != NULL && tree->next[i]->flag == 1)
            searchParentName(tree->next[i], s, parent);
    }
}

void read(int t)
{
    char name[21], parname[21];
    int flag, date;
    while (t--)
    {
        fscanf(fin, "%s%s%d%d", name, parname, &flag, &date);
        struct File *p = (struct File *)malloc(sizeof(struct File));
        strcpy(p->name, name);
        strcpy(p->parentname, parname);
        p->flag = flag;
        p->date = date;
        searchParentName(root, p->parentname, &p->parent);
        p->layer = p->parent->layer + 1;
        p->degree = 0;
        p->pos = p->parent->degree;
        p->parent->next[p->parent->degree++] = p;
    }
}
int findn;
void find_store(struct File *tree, char s[])
{
    if (tree != NULL)
        if (tree->flag == 0 && strcmp(tree->name, s) == 0)
        {
            allfind[findn++] = tree;
            return;
        }

    for (int i = 0; i < tree->degree; i++)
    {
        if (tree->next[i] != NULL)
            find_store(tree->next[i], s);
    }
}
char stack[10010][51];
int top = -1;
void dfs(struct File *root, struct File *find)
{
    struct File *p = find;
    while (p != root)
    {
        strcpy(stack[++top], p->name);
        p = p->parent;
    }
    strcpy(stack[++top], root->name);
}
void print()
{
    for (int i = 0; i < findn; i++)
    {

        dfs(root, allfind[i]);
        printf("%s:", stack[top--]);
        while (top != -1)
        {
            printf("\\%s", stack[top--]);
        }
        putchar('\n');
    }
}
void preorder(struct File *root)
{
    static int n = 1;
    if (root->flag == 0)
        root->pos = n++;
    if (root != NULL)
        for (int i = 0; i < root->degree; i++)
        {
            if (root->next[i] != NULL)
                preorder(root->next[i]);
        }
}
int main()
{
    fin = fopen("files.txt", "r");
    scanf("%d%s", &n, stringf);
    root = (struct File *)malloc(sizeof(struct File));
    fscanf(fin, "%s%s%d%d", root->name, root->parentname, &root->flag, &root->date);
    root->parent = NULL;
    root->layer = 0;
    root->degree = 0;
    read(n);
    find_store(root, stringf);
    preorder(root);
    qsort(allfind, findn, sizeof(struct File *), cmp);
    print();
    return 0;
}
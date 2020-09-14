#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
struct Node
{
    char str[46];
    int cnt;
    struct Node *left, *right;
} * bstree;
int nodecnt = 0;
typedef struct Node node;
FILE *in;
node *insertBST(char *s)
{
    node *q, *p = (node *)malloc(sizeof(node));
    strcpy(p->str, s);
    p->cnt = 1;
    p->left = NULL;
    p->right = NULL;
    if (bstree == NULL)
        bstree = p;
    else
    {
        q = bstree;
        while (1)
        {
            if (strcmp(s, q->str) < 0)
            {
                if (q->left == NULL)
                {
                    q->left = p;
                    break;
                }
                else
                    q = q->left;
            }
            else if (strcmp(s, q->str) > 0)
            {
                if (q->right == NULL)
                {
                    q->right = p;
                    break;
                }
                else
                    q = q->right;
            }
            else
            {
                q->cnt++;
                free(p);
                break;
            }
        }
    }
    return bstree;
}
void readword()
{
    char *s = (char *)malloc(sizeof(char) * 46);
    char temp;
    int i = 0;
    *s = '\0';
    while ((temp = fgetc(in)) != EOF)
    {
        if (96 < temp && 123 > temp)
        {
            *(s + (i++)) = temp;
        }
        else if (64 < temp && 91 > temp)
        {
            *(s + (i++)) = temp + 32;
        }
        else
        {
            if (*s != '\0')
            {
                *(s + i) = '\0';
                bstree = insertBST(s);
            }
            i = 0;
            *s = '\0';
        }
    }
    free(s);
}
void preorder(node *a[], node *tree)
{

    if (tree == NULL)
        return;
    a[nodecnt++] = tree;
    preorder(a, tree->left);
    preorder(a, tree->right);
}
int cmp(const void *a, const void *b)
{
    node **c = (node **)a;
    node **d = (node **)b;
    return strcmp((*c)->str, (*d)->str);
}
int main()
{
    in = fopen("article.txt", "r");
    readword();
    if (bstree != NULL && bstree->right != NULL && bstree->right->right != NULL)
        printf("%s %s %s\n", bstree->str, bstree->right->str, bstree->right->right->str);
    else if (bstree != NULL && bstree->right != NULL)
        printf("%s %s\n", bstree->str, bstree->right->str);
    else if (bstree != NULL)
        printf("%s\n", bstree->str);
    node *arr[10005];
    preorder(arr, bstree);
    qsort(arr, nodecnt, sizeof(node *), cmp);
    for (int i = 0; i < nodecnt; i++)
        printf("%s %d\n", arr[i]->str, arr[i]->cnt);
    return 0;
}
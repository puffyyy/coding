#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
typedef int datatype;
struct Node
{
    datatype val;
    int layer;
    struct Node *left, *right;
} * bstree;
typedef struct Node node;
node *creatNode(datatype tmp)
{
    node *q, *p = (node *)malloc(sizeof(node));
    p->val = tmp;
    p->left = NULL;
    p->right = NULL;
    p->layer = 0;
    if (bstree == NULL)
        bstree = p;
    else
    {
        q = bstree;
        while (1)
        {
            if (tmp < q->val)
            {
                if (q->left == NULL)
                {
                    q->left = p;
                    break;
                }
                else
                    q = q->left;
            }
            else if (tmp >= q->val)
            {
                if (q->right == NULL)
                {
                    q->right = p;
                    break;
                }
                else
                    q = q->right;
            }
        }
    }
    return bstree;
}
void preorder(node *tree)
{
    if (tree == NULL)
        return;
    static int deepth = 1;

    tree->layer = deepth;
    if (tree->left == NULL && tree->right == NULL)
        printf("%d %d\n", tree->val, tree->layer);
    deepth++;
    preorder(tree->left);

    preorder(tree->right);
    deepth--;
}
int main()
{
    int n, tmp;
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &tmp);
        bstree = creatNode(tmp);
    }
    preorder(bstree);

    return 0;
}
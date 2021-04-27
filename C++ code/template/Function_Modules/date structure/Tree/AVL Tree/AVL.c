#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
//不能有相同元素
#define MAX(a, b) ((a) > (b) ? (a) : (b))
typedef int dataType;
typedef struct AVLTreeNode
{
    dataType data;
    int height;
    struct AVLTreeNode *left;
    struct AVLTreeNode *right;
} Node, *AVLTree;

AVLTree root = NULL;

int AVLTree_Height(AVLTree p)
{
    //获取AVL树 节点 的高度
    return (p == NULL) ? 0 : (p->height);
}
Node *minimumAVLNode(AVLTree T)
{
    Node *p = T;
    if (p == NULL)
        return NULL;
    while (p->left != NULL)
        p = p->left;
    return p;
}
Node *maximumAVLNode(AVLTree T)
{
    Node *p = T;
    if (p == NULL)
        return NULL;
    while (p->right != NULL)
        p = p->right;
    return p;
}
Node *rightRotation(AVLTree T)
{
    AVLTree L = T->left;
    T->left = L->right;
    L->right = T;
    T->height = MAX(AVLTree_Height(T->left), AVLTree_Height(T->right)) + 1;
    L->height = MAX(AVLTree_Height(L->left), AVLTree_Height(L->right)) + 1;
    return L;
}
Node *leftRotation(AVLTree T)
{
    AVLTree R = T->right;
    T->right = R->left;
    R->left = T;
    T->height = MAX(AVLTree_Height(T->left), AVLTree_Height(T->right)) + 1;
    R->height = MAX(AVLTree_Height(R->left), AVLTree_Height(R->right)) + 1;
    return R;
}
Node *left_rightRotation(AVLTree T)
{
    T->left = leftRotation(T->left);
    return rightRotation(T);
}
Node *right_leftRotation(AVLTree T)
{
    T->right = rightRotation(T->right);
    return leftRotation(T);
}
Node *createAVLNode(dataType item, Node *left, Node *right)
{
    Node *p;
    if ((p = (Node *)malloc(sizeof(Node))) == NULL)
        return NULL;
    p->data = item;
    p->height = 0;
    p->left = left;
    p->right = right;

    return p;
}
Node *insertAVLNode(AVLTree Tree, dataType item)
{

    if (Tree == NULL) //叶子节点
    {
        // 新建节点
        Tree = createAVLNode(item, NULL, NULL);
        if (Tree == NULL)
        {
            printf("ERROR: create AVLTree node failed!\n");
            return NULL;
        }
    }
    else if (item < Tree->data) // 应该将item插入Tree的左子树
    {
        Tree->left = insertAVLNode(Tree->left, item);
        // 插入节点后，若AVL树失去平衡，则进行相应的调节。
        if (AVLTree_Height(Tree->left) - AVLTree_Height(Tree->right) == 2)
        {
            if (item < Tree->left->data)
                Tree = rightRotation(Tree);
            else
                Tree = left_rightRotation(Tree);
        }
    }
    else if (item > Tree->data)
    {
        Tree->right = insertAVLNode(Tree->right, item);
        if (AVLTree_Height(Tree->right) - AVLTree_Height(Tree->left) == 2)
        {
            if (item > Tree->right->data)
                Tree = leftRotation(Tree);
            else
                Tree = right_leftRotation(Tree);
        }
    }
    else
    {
        printf("The value already exists\n");
    }
    Tree->height = MAX(AVLTree_Height(Tree->left), AVLTree_Height(Tree->right)) + 1;
    return Tree;
}
Node *searchAVLNode(AVLTree Tree, dataType key)
{
    Node *p = Tree;
    while (p != NULL)
    {
        if (p->data == key)
            return p;
        else if (p->data > key)
            p = p->left;
        else
            p = p->right;
    }
    return NULL;
}
Node *deleteAVLNode(AVLTree Tree, Node *del_node)
{
    if (Tree == NULL || del_node == NULL)
        return NULL;
    if (del_node->data < Tree->data)
    {
        Tree->left = deleteAVLNode(Tree->left, del_node);
        if (AVLTree_Height(Tree->right) - AVLTree_Height(Tree->left) == 2)
        {
            if (del_node->data > Tree->right->data)
                Tree = leftRotation(Tree);
            else
                Tree = right_leftRotation(Tree);
        }
    }
    else if (del_node->data > Tree->data)
    {
        Tree->right = deleteAVLNode(Tree->right, del_node);
        if (AVLTree_Height(Tree->left) - AVLTree_Height(Tree->right) == 2)
        {
            if (del_node->data < Tree->left->data)
                Tree = rightRotation(Tree);
            else
                Tree = left_rightRotation(Tree);
        }
    }
    // Tree是对应要删除的节点
    else if (del_node->data == Tree->data)
    {
        // Tree的左右孩子都非空
        if ((Tree->left) && (Tree->right))
        {
            if (AVLTree_Height(Tree->left) > AVLTree_Height(Tree->right))
            {
                // 如果Tree的左子树比右子树高；
                // 则(01)找出Tree的左子树中的最大节点
                //   (02)将该最大节点的值赋值给Tree。
                //   (03)删除该最大节点。
                // 这类似于用"Tree的左子树中最大节点"做"Tree"的替身；
                // 采用这种方式的好处是：删除"Tree的左子树中最大节点"之后，AVL树仍然是平衡的。
                Node *max = maximumAVLNode(Tree->left);
                Tree->data = max->data;
                Tree->left = deleteAVLNode(Tree->left, max);
            }
            else
            {
                // 如果Tree的左子树不比右子树高(即它们相等，或右子树比左子树高1)
                // 则(01)找出Tree的右子树中的最小节点
                //   (02)将该最小节点的值赋值给Tree。
                //   (03)删除该最小节点。
                // 这类似于用"Tree的右子树中最小节点"做"Tree"的替身；
                // 采用这种方式的好处是：删除"Tree的右子树中最小节点"之后，AVL树仍然是平衡的。
                Node *min = minimumAVLNode(Tree->right);
                Tree->data = min->data;
                Tree->right = deleteAVLNode(Tree->right, min);
            }
        }
        else
        {
            Node *tmp = Tree;
            Tree = Tree->left ? Tree->left : Tree->right;
            free(tmp);
            tmp=NULL;
        }
    }
    if (Tree != NULL)
        Tree->height = MAX(AVLTree_Height(Tree->left), AVLTree_Height(Tree->right)) + 1;

    return Tree;
}
void destoryAVLTree(AVLTree Tree)
{
    if (Tree == NULL)
        return;
    if (Tree->left != NULL)
        destoryAVLTree(Tree->left);
    if (Tree->right != NULL)
        destoryAVLTree(Tree->right);
    free(Tree);
}
void preorderAVLTree(AVLTree Tree)
{
    if (Tree != NULL)
    {
        printf("%d ", Tree->data);
        preorderAVLTree(Tree->left);
        preorderAVLTree(Tree->right);
    }
}
void inorderAVLTree(AVLTree Tree)
{
    if (Tree != NULL)
    {
        inorderAVLTree(Tree->left);
        printf("%d ", Tree->data);
        inorderAVLTree(Tree->right);
    }
}
int main()
{
    int arr[] = {3, 2, 1, 4, 5, 6, 7, 16, 15, 14, 13, 12, 11, 10, 8, 9};
    for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); i++)
        root = insertAVLNode(root, arr[i]);
    deleteAVLNode(root,searchAVLNode(root,8));
    printf("\n== ");
    inorderAVLTree(root);
    return 0;
}

//https://www.cnblogs.com/skywang12345/p/3576969.html#aa1
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define MAXSIZE 501
typedef int dataType;
enum oper
{
    EQU,
    ADD,
    MIN,
    MUL,
    DIV,
    MOD,
    LEFT,
    RIGHT
};
enum symbol
{
    NUM,
    OP,
    EQ,
    OTHER
};
int PRI[] = {-1, 0, 0, 1, 1, 1, 2, 2};
struct sym
{
    union {
        dataType num;
        enum oper op;
    };
    char isNum;
};
struct sym Postfix[MAXSIZE];
static int PostfixPos = -1;
struct sym opStack[MAXSIZE];
static int oTop = -1;
enum symbol getSym(struct sym *item)
{
    int c, n;
    while ((c = getchar()) != '=')
    {
        if (c >= '0' && c <= '9')
        {
            for (n = 0; c >= '0' && c <= '9'; c = getchar())
                n = n * 10 + c - '0';
            ungetc(c, stdin);
            item->num = n;
            item->isNum = 'Y';
            return NUM;
        }
        else
        {
            item->isNum = 'N';
            switch (c)
            {
            case '+':
                item->op = ADD;
                return OP;
            case '-':
                item->op = MIN;
                return OP;
            case '*':
                item->op = MUL;
                return OP;
            case '/':
                item->op = DIV;
                return OP;
            case '%':
                item->op = MOD;
                return OP;
            case '(':
                item->op = LEFT;
                return OP;
            case ')':
                item->op = RIGHT;
                return OP;
            case ' ':
            case '\t':
            case '\n':
                break; //重新读入字符
            default:
                return OTHER;
            }
        }
    }

    return EQ;
}
char opToChar(enum oper op)
{
    switch (op)
    {
    case ADD:
        return '+';
    case MIN:
        return '-';
    case MUL:
        return '*';
    case DIV:
        return '/';
    case MOD:
        return '%';
    case LEFT:
        return '(';
    case RIGHT:
        return ')';
    default:
        return ' ';
    }
}
void addPostfix(struct sym item)
{
    Postfix[++PostfixPos] = item;
}
void pushOp(struct sym op)
{
    if (oTop == MAXSIZE - 1)
    {
        printf("operator stack is full!\n");
    }
    opStack[++oTop] = op;
}
struct sym topOp()
{
    if (oTop == -1)
        ;
    return opStack[oTop];
}
struct sym popOp()
{
    if (oTop != -1)
    {
        return opStack[oTop--];
    }
    else
        printf("oTop=-1\n");
}
//*******************expression tree*******************//
struct expressionTreeNode
{
    struct sym item;
    struct expressionTreeNode *left, *right;
} * root;
typedef struct expressionTreeNode node;
node *treeAddressStack[MAXSIZE];
int treeTop = -1;
node *creatTreeNode(struct sym item)
{
    node *p = (node *)malloc(sizeof(node));
    p->item = item;
    p->left = NULL;
    p->right = NULL;
    return p;
}
void pushTreeNode(node *tree)
{
    if (treeTop == MAXSIZE - 1)
        printf("treeTop=MAXSIZE-1\n");
    treeAddressStack[++treeTop] = tree;
}
node *popTreeNode()
{
    if (treeTop == -1)
        printf("treeTop=-1\n");
    return treeAddressStack[treeTop--];
}
node *combineTreeNode(node *tree)
{
    tree->right = popTreeNode();
    tree->left = popTreeNode();
    return tree;
}
int postOrderCalculate(node *tree)
{
    // if(tree==NULL)return 0;
    if (tree->item.isNum == 'Y')
        return tree->item.num;
    else if (tree->item.isNum == 'N')
    {
        switch (tree->item.op)
        {
        case ADD:
            return postOrderCalculate(tree->left) + postOrderCalculate(tree->right);
        case MIN:
            return postOrderCalculate(tree->left) - postOrderCalculate(tree->right);
        case MUL:
            return postOrderCalculate(tree->left) * postOrderCalculate(tree->right);
        case DIV:
            return postOrderCalculate(tree->left) / postOrderCalculate(tree->right);
        }
    }
}
int main()
{
    struct sym item;
    enum symbol s;
    while ((s = getSym(&item)) != EQ)
    {
        if (s == NUM)
            addPostfix(item);
        else if (s == OP)
        {
            struct sym t;
            if (item.op != RIGHT)
            {
                while (PRI[topOp().op] >= PRI[item.op] && topOp().op != LEFT)
                {
                    addPostfix(popOp());
                }
                pushOp(item);
            }
            else
            {
                while ((t = popOp()).op != LEFT)
                    addPostfix(t);
            }
        }
        else
            continue;
    }
    while (oTop >= 0)
        addPostfix(popOp());
    //中缀转后缀表达式 Postfix[]
    for (int i = 0; i <= PostfixPos; i++)
    {
        if (Postfix[i].isNum == 'Y')
            pushTreeNode(creatTreeNode(Postfix[i]));
        else
        {
            pushTreeNode(combineTreeNode(creatTreeNode(Postfix[i])));
        }
    }
    root = popTreeNode();
    if (root != NULL && root->left != NULL && root->right != NULL)
    {
        if (root->item.isNum == 'Y')
            printf("%d ", root->item.num);
        else
            printf("%c ", opToChar(root->item.op));
        if (root->left->item.isNum == 'Y')
            printf("%d ", root->left->item.num);
        else
            printf("%c ", opToChar(root->left->item.op));
        if (root->right->item.isNum == 'Y')
            printf("%d \n", root->right->item.num);
        else
            printf("%c \n", opToChar(root->right->item.op));
    }
    else if (root != NULL)
    {
        if (root->item.isNum == 'Y')
            printf("%d ", root->item.num);
        else
            printf("%c \n", opToChar(root->item.op));
    }

    printf("%d", postOrderCalculate(root));
    return 0;
}
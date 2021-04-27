/*
后缀建树
前缀建树
表达式树后缀遍历计算
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXSIZE 101
union sym {
    int num;
    char op;
};
enum symbol
{
    NUM,
    OP,
    END,
    OTHER
};
typedef struct expresstionTreeNode
{
    union {
        int num;
        char op;
    };
    enum symbol flag;
    struct expresstionTreeNode *left;
    struct expresstionTreeNode *right;
} Tnode;
enum symbol getsym(union sym *item, char post[], int *pos)
{
    int n;
    char c;
    while ((c = post[*pos]) != '\0')
    {
        if (c >= '0' && c <= '9')
        {
            for (n = 0; c >= '0' && c <= '9'; c = post[++(*pos)])
                n = n * 10 + c - '0';
            *pos--;
            item->num = n;
            return NUM;
        }
        else
        {
            ++*pos;
            switch (c)
            {

            case '+':
                item->op = '+';
                return OP;
            case '-':
                item->op = '-';
                return OP;
            case '*':
                item->op = '*';
                return OP;
            case '/':
                item->op = '/';
                return OP;
            case '%':
                item->op = '%';
                return OP;
            case '(':
                item->op = '(';
                return OP;
            case ')':
                item->op = ')';
                return OP;
            case ' ':
            case '\t':
            case '\n':
                break;
            default:
                return OTHER;
            }
        }
    }
    return END;
}
Tnode *postfix_buildtree(char post[])
{
    int postpos = 0;
    enum symbol types;
    union sym item;
    Tnode *treestack[MAXSIZE];
    int top = -1;
    while ((types = getsym(&item, post, &postpos)) != END)
    {
        if (types == NUM)
        {
            Tnode *p = (Tnode *)malloc(sizeof(Tnode));
            p->num = item.num;
            p->flag = NUM;
            p->left = NULL;
            p->right = NULL;
            treestack[++top] = p;
        }
        else if (types == OP)
        {
            Tnode *p = (Tnode *)malloc(sizeof(Tnode));
            p->op = item.op;
            p->flag = OP;
            p->right = treestack[top--];
            p->left = treestack[top--];
            treestack[++top] = p;
        }
    }
    return treestack[top--];
}
Tnode *prefix_buildtree(char pre[])
{
    static int prepos;
    enum symbol types;
    union sym item;
    types = getsym(&item, pre, &prepos);
    if (types == NUM)
    {
        Tnode *p = (Tnode *)malloc(sizeof(Tnode));
        p->num = item.num;
        p->flag = NUM;
        p->left = NULL;
        p->right = NULL;
        return p;
    }
    else if (types == OP)
    {
        Tnode *p = (Tnode *)malloc(sizeof(Tnode));
        p->op = item.op;
        p->flag = OP;
        p->left = prefix_buildtree(pre);
        p->right = prefix_buildtree(pre);
        return p;
    }
    else
    {
        printf("pre buildtree error !");
        exit(1);
    }
}
void inorder(Tnode *root)
{
    if (root == NULL)
        return;
    inorder(root->left);
    if (root->flag == NUM)
        printf("%d ", root->num);
    else
        printf("%c", root->op);
    inorder(root->right);
}

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
union Sym {
    int num;
    enum oper op;
};
int PRI[] = {-1, 0, 0, 1, 1, 1, 2, 2};
enum oper stack[MAXSIZE];
int TOP = -1;
int isempty()
{
    return TOP == -1;
}
void push(enum oper x)
{
    stack[++TOP] = x;
}
enum oper top()
{
    return stack[TOP];
}
enum oper pop()
{
    return stack[TOP--];
}

enum symbol getSym(union Sym *item, char infix[], int *i)
{
    int c, n;
    while ((c = infix[*i]) != '\0')
    {
        if (c >= '0' && c <= '9')
        {
            for (n = 0; c >= '0' && c <= '9'; c = infix[++(*i)])
                n = n * 10 + c - '0';
            *i--;
            item->num = n;
            return NUM;
        }
        else
        {
            ++*i;
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
                break;
            default:
                return OTHER;
            }
        }
    }
    return END;
}

char op_to_c(enum oper op)
{
    switch (op)
    {
    case ADD:
        return '+';
        break;
    case MIN:
        return '-';
        break;
    case MUL:
        return '*';
        break;
    case DIV:
        return '/';
        break;
    case MOD:
        return '%';
        break;
    }
    return -1;
}

void transfer_infix_to_postfix_expression(char infix[], char post[])
{
    union Sym item;
    enum symbol s;
    enum oper t;
    int postpos = 0, infixpos = 0;
    while ((s = getSym(&item, infix, &infixpos)) != END)
    {
        if (s == NUM)
        {
            int lenth = 0;
            int temp, n = item.num;
            char a[10];
            while (n != 0)
            {
                temp = n % 10;
                n /= 10;
                a[lenth++] = temp + '0';
            }
            for (lenth--; lenth >= 0; lenth--)
            {
                post[postpos++] = a[lenth];
            }
            post[postpos++] = ' ';
        }
        else if (s == OP)
        {
            if (item.op != RIGHT)
            {
                while (PRI[item.op] <= PRI[top()] && top() != LEFT)
                {
                    post[postpos++] = op_to_c(pop());
                }
                push(item.op);
            }
            else
                while ((t = pop()) != LEFT)
                    post[postpos++] = op_to_c(t);
        }
    }
    while (!isempty())
    {
        post[postpos++] = op_to_c(pop());
    }
    post[postpos++] = '\0';
}
int preorder_Compute_with_expressiontree(Tnode *root)
{
    if (root == NULL)
        return 0;
    if (root->flag == NUM)
        return root->num;
    int a = 0;
    switch (root->op)
    {
    case '+':
        a = preorder_Compute_with_expressiontree(root->left) + preorder_Compute_with_expressiontree(root->right);
        break;
    case '-':
        a = preorder_Compute_with_expressiontree(root->left) - preorder_Compute_with_expressiontree(root->right);
        break;
    case '*':
        a = preorder_Compute_with_expressiontree(root->left) * preorder_Compute_with_expressiontree(root->right);
        break;

    case '/': //注意 root->right 不能为0!!!!
        a = preorder_Compute_with_expressiontree(root->left) / preorder_Compute_with_expressiontree(root->right);
        break;
    default:
        break;
    }
    return a;
}
int main()
{
    char prefix[MAXSIZE], infix[MAXSIZE], postfix[MAXSIZE];

    /*
    gets(prefix);
    Tnode *root = prefix_buildtree(prefix);
    */

    /*
    gets(postfix);
    Tnode *root = postfix_buildtree(postfix);
    */

    //inorder(root);

    /*
    gets(infix);
    transfer_infix_to_postfix_expression(infix, postfix);
    Tnode *root = postfix_buildtree(postfix);
    inorder(root);
    int ans = preorder_Compute_with_expressiontree(root);
    printf("\n%d", ans);
    */
    return 0;
}
//1 2 3 + 4 * + 5 -
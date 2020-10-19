void Preorder(struct BiTNode *t)
{
    struct BiTNode *St[MaxSize], *p;
    int top = 0; //置空栈
    if (t ! = NULL)
    {
        St[top++] = t;
        while (top)
        {
            p = St[--top];
            printf("%c ", p->data);
            if (p->rchild != NULL)
                St[top++] = p->rchild;
            if (p->lchild != NULL)
                St[top++] = p->lchild;
        }
        printf("\n");
    }
}
void Midorder(struct BiTNode *t) //t为根指针
{
    struct BiTNode *st[maxleng]; //定义指针栈
    int top = 0；                //置空栈
        do
    {
        while (t) //根指针t表示的为非空二叉树
        {
            if (top == maxleng)
                exit(OVERFLOW) ；       //栈已满,退出
                    st[top++] = t；     //根指针进栈
                        t = t->lchild； //t移向左子树
        }                               //循环结束表示以栈顶元素的指向为根结点的二叉树
                                        //的左子树遍历结束
        if (top)                        //为非空栈
        {
            t = st[--top] ；             //弹出根指针
                printf("%c", t->data) ； //访问根结点
                    t = t->rchild；      //遍历右子树
        }
    }
    while (top || t)
        ； //父结点未访问，或右子树未遍历
}

void Postorder(struct BiTNode *t)
{
    struct BiTNode *St[MaxSize], *pre;
    int flag, top = 0;
    if (t != NULL)
    {
        do
        {
            while (t != NULL)
            {
                St[top++] = t;
                t = t->lchild;
            }
            pre = NULL;
            flag = 1;
            while (top && flag)
            {
                t = St[top - 1];
                if (t->rchild == pre)
                {
                    printf(“% c ”, t->data);
                    top--;
                    pre = t;
                }
                else
                {
                    t = t->rchild;
                    flag = 0;
                }
            }
        } while (top);
        printf(“\n”);
    }
}

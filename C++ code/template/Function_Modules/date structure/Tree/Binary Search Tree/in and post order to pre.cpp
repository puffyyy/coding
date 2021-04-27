//由遍历序列恢复二叉树
#include <iostream>
using namespace std;
template <class T>
class Btree;

template <class T>
class Node
{
    friend class Btree<T>;

private:
    T data;
    Node *left, *right;

public:
    Node()
    {
        left = NULL;
        right = NULL;
    };
    Node(const T &e, Node *L = NULL, Node *R = NULL)
    {
        data = e;
        left = L;
        right = R;
    };
};

template <class T>
class Btree
{
private:
    Node<T> *root;
    T stopFlag;
    void PreOrder(Node<T> *t);

public:
    Btree() { root = NULL; };
    void createTree(const T &flag);
    void PreOrder();
    Node<T> *buildTree(T post[], int pl, int pr, T mid[], int ml, int mr);
    Node<T> *buildBTree(T post[], T mid[], int n);
};

template <class T>
void Btree<T>::PreOrder()
{
    PreOrder(root);
}

template <class T>
void Btree<T>::PreOrder(Node<T> *t)
{
    if (!t)
        return;
    cout << t->data << ' ';
    PreOrder(t->left);
    PreOrder(t->right);
}
template <class T>
Node<T> *Btree<T>::buildBTree(T post[], T mid[], int n) //the easy one
{
    if (n == 0)
        return NULL;

    Node<T> *p;
    int i;
    p = new Node<T>(post[n - 1]);
    if (!root)
        root = p;
    for (i = 0; i < n; i++)
        if (mid[i] == post[n - 1])
            break;
    p->left = buildBTree(post, mid, i);
    p->right = buildBTree(post + i, mid + i + 1, n - i - 1);
    return p;
}
/*
BinTree Translate(char*preorder,char *inorder,int len)
{
	if(len==0)
		return NULL;
	int rootIndex=0;
    struct TNode* t=new TNode;
    t->Data=*preorder;
    for(;rootIndex<len;rootIndex++)
    {
    	if(inorder[rootIndex]==*preorder)
    	 break;
	}
	t->Left=Translate(preorder+1,inorder,rootIndex);
	t->Right=Translate(preorder+rootIndex+1,inorder+rootIndex+1,len-(rootIndex+1));
	return t;
}
*/
template <class T>
Node<T> *Btree<T>::buildTree(T post[], int pl, int pr, T mid[], int ml, int mr)
{
    Node<T> *p, *leftRoot, *rightRoot;
    int i, pos, num;
    int lpl, lpr, lml, lmr;
    int rpl, rpr, rml, rmr;
    if (pl > pr || ml > mr)
        return NULL;
    p = new Node<T>(post[pr]);
    if (!root)
        root = p;
    for (i = ml; i <= mr; i++)
        if (mid[i] == post[pr])
            break;
    pos = i;
    num = pos - ml;
    lpl = pl;
    lpr = lpl + num - 1;
    lml = ml;
    lmr = lml + num - 1;
    leftRoot = buildTree(post, lpl, lpr, mid, lml, lmr);
    rpl = pl + num;
    rpr = pr - 1;
    rml = pos + 1;
    rmr = mr;
    rightRoot = buildTree(post, rpl, rpr, mid, rml, rmr);
    p->left = leftRoot;
    p->right = rightRoot;
    return p;
}
int main()
{
    int n;
    cin >> n;
    int *post = new int[n];
    int *mid = new int[n];
    for (int i = 0; i < n; i++)
    {
        cin >> mid[i];
    }
    for (int i = 0; i < n; i++)
    {
        cin >> post[i];
    }
    int pl, pr;
    pl = 0;
    pr = n - 1;
    int ml, mr;
    ml = 0;
    mr = n - 1;
    Btree<int> tree;
    tree.Btree<int>::buildTree(post, pl, pr, mid, ml, mr);
    //tree.Btree<int>::buildBTree(post, mid, n);
    tree.PreOrder();
    return 0;
}
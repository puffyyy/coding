#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <cstdlib>
#include <algorithm>
#include <queue>
using namespace std;
typedef long long int ll;
int a[2500], b[2500];
struct tree
{
    int val;
    tree *left, *right;
    tree(int val_ = -1, tree *left_ = NULL, tree *right_ = NULL) : val(val_), left(left_), right(right_) {}
    bool fullequal(const tree &t) const
    {
        return val == t.val && left->val == t.left->val && right->val == t.right->val;
    }
};
tree *creatTree(int a[], int len)
{
    queue<tree *> que;
    int pos = 1;

    tree *root = new tree(a[1]);
    root->left = new tree(-1), root->right = new tree(-1);
    que.push(root->left), que.push(root->right);

    while (pos < len)
    {
        tree *tmp = que.front();
        tmp->val = a[++pos];
        que.pop();
        tmp->left = new tree(-1), tmp->right = new tree(-1);
        que.push(tmp->left), que.push(tmp->right);
    }
    return root;
}
bool isequal(tree *a, tree *b)
{
    if (a == NULL && b == NULL)
        return true;
    if (!a || !b)
        return false;
    if (a->val == b->val)
    {
        return (isequal(a->left, b->left) && isequal(a->right, b->right)) || (isequal(a->left, b->right) && isequal(a->right, b->left));
    }
    else
        return false;
}
int main()
{
    int t, k;
    scanf("%d", &t);
    while (t--)
    {
        scanf("%d", &k);
        int pos = 1;
        for (int i = 0, size = 1; i <= k; ++i)
        {
            size <<= 1;
            for (; pos < size; ++pos)
                scanf("%d", &a[pos]);
        }
        tree *ta = creatTree(a, pos - 1);
        pos = 1;
        for (int i = 0, size = 1; i <= k; ++i)
        {
            size <<= 1;
            for (; pos < size; ++pos)
                scanf("%d", &b[pos]);
        }
        tree *tb = creatTree(b, pos - 1);
        if (isequal(ta, tb))
            printf("Yes\n");
        else
            printf("No\n");
    }
    return 0;
}
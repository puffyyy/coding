#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include <stack>
#include <queue>
#include <set>
#include "file_read.h"
#include "count_by_trie.h"
using namespace std;
typedef long long ll;
extern int len;
extern const int MS;
extern long long word_cnt, all_cnts;
extern struct Word words[MS];
double p[MS];
double w[MS][MS], e[MS][MS];
int root[MS][MS];
struct Dic
{
    int pos;
    // char str[48];
    struct Dic *left, *right;
};
void obst()
{
    for (int i = 0; i < len; i++)
        p[i] = (double)words[i].cnt / (double)all_cnts;
    for (int i = 0; i < len; i++)
    {
        e[i][i] = w[i][i] = p[i];
        root[i][i] = i;
    }
    int k1, k2;
    for (int l = 2; l <= len; l++)
    {
        for (int i = 0; i < len - l + 1; i++)
        {
            int j = i + l - 1;
            w[i][j] = w[i][j - 1] + p[i];
            k1 = root[i][j - 1];
            k2 = root[i + 1][j];
            if (e[i][k1 - 1] + e[k1 + 1][j] < e[i][k2 - 1] + e[k2 + 1][j])
            {
                e[i][j] = e[i][k1 - 1] + e[k1 + 1][j] + w[i][j];
                root[i][j] = k1;
            }
            else
            {
                e[i][j] = e[i][k2 - 1] + e[k2 + 1][j] + w[i][j];
                root[i][j] = k2;
            }
        }
    }
}
struct Dic *build_tree(int l, int r)
{
    if (r < l)
        return NULL;
    int mid = root[l][r];
    struct Dic *root_node = (struct Dic *)malloc(sizeof(struct Dic));
    if (root_node == NULL)
    {
        printf("wrong with malloc\n");
    }
    root_node->pos = mid;

    // strcpy(root_node->str, words[mid].str);
    root_node->left = build_tree(l, mid - 1);
    root_node->right = build_tree(mid + 1, r);
    return root_node;
}
void preorder(struct Dic *root, FILE *fout_res)
{
    if (root == NULL)
        return;
    fprintf(fout_res, "root: no.%-5d:%-30s frequency: %d\n", root->pos, words[root->pos].str, words[root->pos].cnt);
    if (root->left)
        fprintf(fout_res, "|left: no.%-4d:%-30s ", root->left->pos, words[root->left->pos].str, words[root->left->pos].cnt);
    if (root->right)
        fprintf(fout_res, "|right: no.%-4d:%-30s", root->right->pos, words[root->right->pos].str, words[root->right->pos].cnt);
    if (root->left || root->right)
        fprintf(fout_res, "\n");
    preorder(root->left, fout_res);
    preorder(root->right, fout_res);
}

int main()
{
    FILE *fin_book = fopen("book.txt", "r");
    FILE *fout_count = fopen("count.txt", "w");
    FILE *fout_res = fopen("res.txt", "w");
    FILE *fin_count = fopen("count.txt", "r");

    node *root = build_trie(fin_book);
    fprintf(fout_count, "Words Cnts:%6lld                        Number of Occurrences:%6lld\n", word_cnt, all_cnts);
    preorder_trie(root, -1, fout_count);
    // file_read_wordcnt(fin_count, words);
    obst();

    fprintf(fout_res, "Search Cost of OBST :%lf\n", e[0][len - 1]);
    struct Dic *Dic_root = build_tree(0, len - 1);
    preorder(Dic_root, fout_res);
    return 0;
}
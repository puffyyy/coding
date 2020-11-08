#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <cstdlib>
#include <algorithm>
#include "file_read.h"
using namespace std;
struct node
{
    int cnt;
    // int son;
    node *alpha[27];
};
long long word_cnt = 0, all_cnts = 0;
/*********************************/
node *trie_init()
{
    node *root = (node *)malloc(sizeof(node));
    root->cnt = 0;
    // root->son = -1;
    for (int i = 0; i < 26; ++i)
        root->alpha[i] = NULL;
    return root;
}
void trie_insert_word(node *root, char *str)
{
    char ch;
    int i, pos = 0;
    node *now = root;
    while (str[pos])
    {
        ch = str[pos] - 'a';
        if (now->alpha[ch] != NULL)
            now = now->alpha[ch];
        else
        {
            now->alpha[ch] = (node *)malloc(sizeof(node));
            now = now->alpha[ch];
            // now->son = ch;
            now->cnt = 0;
            for (i = 0; i < 26; ++i)
                now->alpha[i] = NULL;
        }
        ++pos;
    }
    if (!now->cnt)
        ++word_cnt;
    ++now->cnt;
    ++all_cnts;
}
node *build_trie(FILE *in)
{
    node *root = trie_init();
    char s[50];
    while (file_read_word(in, s))
    {
        trie_insert_word(root, s);
    }
    return root;
}
void preorder_trie(node *root, int pos, FILE *out)
{
    int i;
    static char str[100000];
    if (root != NULL)
    {
        ++pos;
        if (root->cnt)
        {
            // all_cnt += root->cnt;
            str[pos] = '\0';
            fprintf(out, "%s %d\n", str, root->cnt);
        }
        for (i = 0; i < 26; ++i)
        {
            if (root->alpha[i] != NULL)
            {
                str[pos] = i + 'a';
                preorder_trie(root->alpha[i], pos, out);
            }
        }
    }
    return;
}

int main()
{
    //ios::sync_with_stdio(false);
    FILE *fin = fopen("book.txt", "r");
    FILE *fout = fopen("count.txt", "w");
    node *root = build_trie(fin);

    fprintf(fout, "%lld %lld\n", word_cnt, all_cnts);
    preorder_trie(root, -1, fout);
    return 0;
}
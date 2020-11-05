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
using namespace std;
struct node
{
    int cnt;
    // int son;
    node *alpha[27];
};
/********************************/
/**********read file*************/
inline char gc(FILE *in)
{
    static char buf[100000], *s, *t;
    return (s == t) && (t = (s = buf) + fread(buf, 1, 100000, in)), s == t ? -1 : *s++;
}
int file_read_words(FILE *in, char *s)
{
    static char temp;
    static int i;
    if (in)
    {
        i = 0;
        *s = '\0';
        while ((temp = gc(in)) != EOF)
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
                    return 1;
                }
            }
        }
    }
    return 0;
}
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
    ++now->cnt;
}
node *build_trie(FILE *in)
{
    node *root = trie_init();
    char s[50];
    while (file_read_words(in, s))
    {
        trie_insert_word(root, s);
    }
    return root;
}
void preorder_trie(node *root, int pos, FILE *out)
{
    int i;
    // static int pos = -1;
    static char str[100000];
    if (root != NULL)
    {
        ++pos;
        if (root->cnt)
        {
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
    FILE *fin = fopen("in.txt", "r");
    FILE *fout = fopen("out.txt", "w");
    node *root = build_trie(fin);
    preorder_trie(root, -1, fout);
    return 0;
}
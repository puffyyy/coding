#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct Node
{
    char c;
    int pos;
    struct Node *next;
    struct Node *prior;
} node, *nodeptr;
int check[127];      //32-126为可见字符
char key[96];        //95+'\0'
int ciphertext[127]; //下标是字符
FILE *fin, *fout;
void delete_and_add(char key[])
{
    int i;
    for (i = 0; key[i] != '\0';)
    {
        if (check[key[i]] == 0)
        {
            check[key[i]] = 1;
            i++;
        }
        else
            strcpy(key + i, key + 1 + i);
    }
    for (int j = 32; j < 127; j++)
    {
        if (check[j] == 0)
            key[i++] = j;
    }
    key[95] = '\0';
}
nodeptr creat_list(char key[])
{
    nodeptr head = (nodeptr)malloc(sizeof(node)), tail = head;
    for (int i = 0; i < 95; i++)
    {
        nodeptr p = (nodeptr)malloc(sizeof(node));
        p->c = key[i];
        p->pos = i;
        tail->next = p;
        p->prior = tail;
        tail = p;
    }
    head->next->prior = tail;
    tail->next = head->next; //circle
    return head;
}
nodeptr delete_list_p(nodeptr head, nodeptr p)
{
    if (p == head->next)
    {
        head->next = p->next;
        p->prior->next = head->next;
        p->next->prior = p->prior;
    }
    else
    {
        p->prior->next = p->next;
        p->next->prior = p->prior;
    }
    nodeptr q = p->next;
    free(p);
    p = NULL;
    return q;
}
void init_ciphertext(nodeptr head, char key[])
{
    char temp = key[0];
    nodeptr p = head->next->next;
    int preloct = head->next->pos;
    delete_list_p(head, head->next);
    for (int i = 0; i < 93; i++)
    {
        int n = (int)key[preloct] - 1;
        while (n--)
        {
            p = p->next;
        }
        ciphertext[key[preloct]] = p->c;
        preloct = p->pos;
        p = delete_list_p(head, p);
    }
    ciphertext[key[preloct]] = p->c;
    ciphertext[p->c] = temp;
    //ciphertext[temp]=key[preloct];
}
int main()
{
    fin = fopen("in.txt", "r");
    fout = fopen("in_crpyt.txt", "w");
    if (fin == NULL || fout == NULL)
    {
        printf("can not open.");
        return 0;
    }
    gets(key);
    delete_and_add(key);
    nodeptr head = creat_list(key);
    init_ciphertext(head, key);

    for (int i = 0; i < 96; i++)
        printf("%c", i + 32);
    putchar('\n');
    for (int i = 32; i < 127; i++)
        printf("%c", ciphertext[i]);
    char ch;
    while ((ch = fgetc(fin)) != EOF)
    {
        if (ch > 31 && ch < 127)
            fputc(ciphertext[ch], fout);
        else
            fputc(ch, fout);
    }
    fclose(fin);
    fclose(fout);
    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
char *dictionary[3501];
int indexAZ[27];
FILE *in;
char nc(FILE *in)
{
    static char buf[100000], *p1 = buf, *p2 = buf;
    return p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 100000, in), p1 == p2) ? EOF : *p1++;
}
inline void xstring(char *s, FILE *in)
{
    int c = nc(in);
    if (c == -1)
    {
        *s = -1;
        return;
    }
    while (c <= 65 || c >= 123)
        c = nc(in);
    for (; c > 65 && c < 123; c = nc(in))
        *s++ = c;
    *s = 0;
}

int readWord(FILE *in)
{
    char s[24];
    int i = 0;
    char flag = 'a';
    for (;; i++)
    {
        //xstring(s, in);
        if (fscanf(in, "%s", s) == EOF)
            break;

        if (*s == -1)
            break;
        dictionary[i] = (char *)malloc(sizeof(char) * (strlen(s) + 1));
        strcpy(dictionary[i], s);
        while (flag != *dictionary[i])
        {
            flag++;
            indexAZ[flag - 'a'] = i;
        }
    }
    indexAZ[26] = i + 1;
    return i;
}
int sequenceSearch(char *ch, int n, int *cnt)
{
    int i;
    for (i = 0; i < n; i++)
    {
        ++(*cnt);
        if (strcmp(ch, dictionary[i]) <= 0)
            break;
    }
    if (strcmp(ch, dictionary[i]) == 0)
        return 1;
    else
        return 0;
}
int binarySearch(char *ch, int left, int right, int *cnt)
{
    int mid;
    while (left <= right)
    {
        mid = left + (right - left) / 2;
        ++(*cnt);
        if (strcmp(ch, dictionary[mid]) < 0)
            right = mid - 1;
        else if (strcmp(ch, dictionary[mid]) == 0)
            return 1;
        else
            left = mid + 1;
    }
    return 0;
}
int indexbinarySearch(char *ch, int *cnt)
{
    return binarySearch(ch, indexAZ[*ch - 'a'], indexAZ[*ch - 'a' + 1] - 1, cnt);
}
#define NHASH 3001
#define MULT 37
struct node
{
    int val;
    struct node *next;
} * hashtable[NHASH];
unsigned int hash(char *str)
{
    unsigned int h = 0;
    char *p;
    for (p = str; *p != '\0'; p++)
        h = MULT * h + *p;
    return h % NHASH;
}
struct node *creatNode(int val)
{
    struct node *p = (struct node *)malloc(sizeof(struct node));
    p->val = val;
    p->next = NULL;
    return p;
}
void initHashtable()
{
    for (int i = 0; i < NHASH; ++i)
    {
        hashtable[i] = creatNode(0);
    }
}
void insertNode(int val, struct node *p)
{
    struct node *q = p;
    p = p->next;
    while (p != NULL)
    {
        if (strcmp(dictionary[p->val], dictionary[val]) > 0)
            break;
        q = p;
        p = p->next;
    }
    q->next = creatNode(val);
    q->next->next = p;
}
void creatHashtable(int n)
{
    initHashtable();
    int pos;
    for (int i = 0; i < n; i++)
    {
        pos = hash(dictionary[i]);
        if (hashtable[pos]->next == NULL)
        {
            hashtable[pos]->next = creatNode(i);
        }
        else
        {
            insertNode(i, hashtable[pos]);
        }
    }
}
int hashSearch(char *s, int *cnt)
{
    int pos = hash(s);
    struct node *p = hashtable[pos]->next;
    if (p == NULL)
        ++(*cnt);
    while (p)
    {
        ++(*cnt);
        if (strcmp(dictionary[p->val], s) >= 0)
            break;
        p = p->next;
    }
    if (p == NULL)
        return 0;
    if (strcmp(dictionary[p->val], s) == 0)
        return 1;
    else
        return 0;
}
void search(char *s, int op, int size)
{
    int cnt = 0, ans;
    switch (op)
    {
    case 1:
        ans = sequenceSearch(s, size, &cnt);
        printf("%d %d\n", ans, cnt);
        break;
    case 2:
        ans = binarySearch(s, 0, size - 1, &cnt);
        printf("%d %d\n", ans, cnt);
        break;
    case 3:
        ans = indexbinarySearch(s, &cnt);
        printf("%d %d\n", ans, cnt);
        break;
    case 4:
        ans = hashSearch(s, &cnt);
        printf("%d %d\n", ans, cnt);
        break;
    default:
        break;
    }
}

int main()
{
    in = fopen("dictionary3000.txt", "r");

    char tmp[24];
    int op;
    int n = readWord(in);

    creatHashtable(n);
    //scanf("%s%d", tmp, &op);
    while (scanf("%s%d", tmp, &op) != EOF)
    {
        search(tmp, op, n);
    }
    fclose(in);
    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define tolower(c) (c >= 'A' && c <= 'Z' ? 'a' - 'A' + c : c)
struct Book
{
    char name[51];
    char author[21];
    char press[31];
    char date[11];
} books[505];
FILE *in, *out;
int size;
int cmp(const void *a, const void *b)
{
    struct Book *c = (struct Book *)a;
    struct Book *d = (struct Book *)b;
    int l1, l2, min, flag;
    l1 = strlen(c->name);
    l2 = strlen(d->name);
    min = l1 < l2 ? l1 : l2;
    flag = strncmp(c->name, d->name, min);
    if (flag < 0)
        return -1;
    else if (flag > 0)
        return 1;
    else
        return l1 < l2 ? -1 : 1;
}
int Init()
{
    int i;
    while (~fscanf(in, "%s%s%s%s", books[i].name, books[i].author, books[i].press, books[i].date))
        i++;
    return i;
}
void printlib()
{
    for (int i = 0; i < size; i++)
    {
       fprintf(out, "%-50s%-20s%-30s%-10s\n", books[i].name, books[i].author, books[i].press, books[i].date);
       // printf("%-50s%-20s%-30s%-10s\n", books[i].name, books[i].author, books[i].press, books[i].date);
    }
}
void add_book()
{
    scanf("%s%s%s%s", books[size].name, books[size].author, books[size].press, books[size].date);
    size++;
    qsort(books, size, sizeof(struct Book), cmp);
}
int check(char *ch, char *find)
{
    int i, j, k;
    for (i = 0; *(ch + i) != '\0'; i++)
    {
        for (j = i, k = 0; *(ch + j) != '\0' &&*(find+k)!='\0'&& tolower(*(ch + j)) == tolower(*(find + k)); j++, k++)
            ;
        if (*(find + k) == '\0')
            return 1;
    }
    return 0;
}
void search_ch()
{
    char ch[51];
    scanf("%s", ch);
    for (int i = 0; i < size; i++)
    {
        if (check(books[i].name, ch) == 1)
            printf("%-50s%-20s%-30s%-10s\n", books[i].name, books[i].author, books[i].press, books[i].date);
    }
}
void delete_book()
{
    char ch[51];
    scanf("%s", ch);
    for (int i = 0; i < size;)
    {
        if (check(books[i].name, ch))
        {
            memcpy(&books[i], &books[i + 1], (size - i) * sizeof(struct Book));
            size--;
        }
        else
            i++;
    }
}
void func(int operation)
{
    if (operation == 1)
        add_book();
    if (operation == 2)
        search_ch();
    if (operation == 3)
        delete_book();
}
int main()
{
    int op;
    in = fopen("books.txt", "r");
    out = fopen("ordered.txt", "w");
    if (in == NULL)
        printf("can not open books.txt\n");
    if (out == NULL)
        printf("can not open ordered.txt\n");
    size = Init();
    qsort(books, size, sizeof(struct Book), cmp);
    while (~scanf("%d", &op))
    {
        if (op == 0)
            break;
        else
            func(op);
    }
    printlib();
    fclose(in);
    fclose(out);
    return 0;
}
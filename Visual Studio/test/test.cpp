#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
struct WORD
{
    char* ch;
};
struct WORD dictionary[10001];
FILE* in;
char nc(FILE* in)
{
    static char buf[100000], * p1 = buf, * p2 = buf;
    return p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 100000, in), p1 == p2) ? EOF : *p1++;
}
inline void xstring(char* s, FILE* in)
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
int readWord(FILE* in)
{
    char s[40];
    int i = 0;
    for (;; i++)
    {
        xstring(s, in);
        if (*s == -1)
            break;
        dictionary[i].ch = (char*)malloc(sizeof(char) * (strlen(s) + 1));
        strcpy(dictionary[i].ch, s);
    }
    return i;
}

int main()
{
    in = fopen("dictionary3000.txt", "r");
    int n = readWord(in);

    printf("%d", n);
    return 0;
}
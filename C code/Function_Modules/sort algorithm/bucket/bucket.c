#include <stdio.h>
#include <stdlib.h>
char array[2147483646];
int cnt;
inline char nc()
{
    static char buf[100000], *p1 = buf, *p2 = buf;
    return p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 100000, stdin), p1 == p2) ? EOF : *p1++;
}
inline int read_int()
{

    int tmp = 0;
    char ch = nc();
    for (; (ch == ' ' || ch == '\n' || ch == '\r' || ch == '\t'); ch = nc())
        ;
    for (; !(ch == ' ' || ch == '\n' || ch == '\r' || ch == '\t'); ch = nc())
        if (ch <= '9' && ch >= '0')
            tmp = 10 * tmp + ch - '0';
    return tmp;
}
int main()
{
    int tmp, n;
    scanf("%d", &n);

    for (int i = 0; i < n; i++)
    {
        tmp = read_int();
        if (!array[tmp])
        {
            ++array[tmp];
            ++cnt;
        }
    }
    printf("%d", cnt);
    return 0;
}
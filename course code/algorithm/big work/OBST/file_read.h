#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#ifndef READ
#define READ 1
inline char gc(FILE *in)
{
    static char buf[100000], *s, *t;
    return (s == t) && (t = (s = buf) + fread(buf, 1, 100000, in)), s == t ? -1 : *s++;
}
int file_read_word(FILE *in, char *s)
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
#endif
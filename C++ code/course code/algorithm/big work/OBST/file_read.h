#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#ifndef READ
#define READ 1
const int MS = 9000 + 5;
extern long long word_cnt, all_cnts;
struct Word
{
    int cnt;
    char str[44];
} words[MS];
inline char gc(FILE *in)
{
    static char buf[100000], *s, *t;
    return (s == t) && (t = (s = buf) + fread(buf, 1, 100000, in)), s == t ? -1 : *s++;
}
inline long long read_ll(FILE *in)
{
    long long k = 0, f = 1;
    char c = gc(in);
    while (c < '0' || c > '9')
    {
        if (c == '-')
            f = -1;
        c = gc(in);
    }
    while (c >= '0' && c <= '9')
    {
        k = (k << 1) + (k << 3) + c - 48;
        c = gc(in);
    }
    return k * f;
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
int file_read_wordcnt(FILE *in, struct Word *words)
{
    char s[50];
    long long len = 0;
    long long allcnt = read_ll(in);
    if (word_cnt != allcnt)
        return 0;
    allcnt = read_ll(in);
    if (all_cnts != allcnt)
        return 0;
    long long cnt;
    while (file_read_word(in, s))
    {
        cnt = read_ll(in);
        words[len].cnt = cnt;
        strcpy(words[len].str, s);
        ++len;
    }
    return 1;
}
#endif
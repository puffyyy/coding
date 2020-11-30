#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define ms 100005
void getnext(char T[], int next[]) //如果失配，从子串的第next[j]处再次比较
{                                  //next[j]表示在j当前位置，不包括T[j]元素，前面j-1个元素 前缀等于后缀 相等的元素个数
    int i = 0, j = -1;
    next[i] = j;
    while (T[i] != '\0')
    {
        if (j == -1 || T[i] == T[j])
        {
            i++, j++;
            next[i] = j;
            //next[++i]=++j;
        }
        else
            j = next[j];
    }
}
int kmpindex(char S[], char T[])
{
    int i = 0, j = 0;
    int *next = (int *)malloc((strlen(T) + 1) * sizeof(int));
    getnext(T, next);
    while (S[i] != '\0' && T[j] != '\0')
    {
        if (S[i] == T[j])
            i++, j++;
        else
            j == 0 ? i++ : (j = next[j]);
    }
    free(next); //why trace/breakpoint trap
    if (T[j] == '\0')
        return i - j;
    else
        return -1;
}
char a[ms], b[ms];
int main()
{
    printf("%d", kmpindex(a, c));

    return 0;
}
#include <iostream>
#include <cstdio>
#include <cstring>
typedef long long ll;
int next[300];
char P[300], T[100005];
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
int kmpindex(char S[], char T[], int pos) //int pos
{
    int i = pos, j = 0; //i=pos

    while (S[i] != '\0' && T[j] != '\0')
    {
        if (S[i] == T[j])
            i++, j++;
        else
            j == 0 ? i++ : (j = next[j]);
    }
    if (T[j] == '\0')
        return i - j;
    else
        return -1;
}
int main()
{
    scanf("%s%s", P, T);
    getnext(P, next);
    int flag = 1;
    int pos = 0;
    for (int i = 1; i <= strlen(P); i++)
    {
        if (i % (i - next[i]) == 0)
            flag = (flag > i / (i - next[i]) ? flag : i / (i - next[i]));
    }
    printf("%d\n", flag);
    while (1)
    {
        flag = kmpindex(T, P, pos);
        if (flag == -1)
            break;
        pos = flag + 1;
        printf("pattern occurs with shift %d\n", flag);
    }
    return 0;
}
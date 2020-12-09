#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define LENG256 256
#define SIZE 10000

void PreBmBc(char *pattern, int m, int bmBc[]) //bmBc['c'] 离pattern结尾最近的字符c 距离 结尾的距离
{                                              //使用字符作为下标
    int i = 0;                                 //计算坏字符数组
    for (; i < 256; i++)
        bmBc[i] = m;
    for (i = 0; i < m - 1; i++)
        bmBc[pattern[i]] = m - i - 1;
}
void suffix_old(char *pattern, int m, int suff[])
{
    int i, j;
    suff[m - 1] = m;
    for (i = m - 2; i >= 0; i--)
    {
        j = i;
        while (j >= 0 && pattern[j] == pattern[m - 1 - i + j])
            j--;
        suff[i] = i - j;
    }
}
void suffix(char *pattern, int m, int suff[])
{
    //计算以pattern[i]结尾的后缀 与 以最后一个字符为后缀 的公共后缀串的长度
    int f, g, i;
    //i是当前正准备计算suff[]值的那个位置。
    //f是上一个成功进行匹配的起始位置
    //g是上一次进行成功匹配的失配位置。
    suff[m - 1] = m;
    g = m - 1;
    for (i = m - 2; i >= 0; --i)
    {
        if (i > g && suff[i + m - 1 - f] < i - g)
            suff[i] = suff[i + m - 1 - f];
        else
        {
            if (i < g)
                g = i;
            f = i;
            while (g >= 0 && pattern[g] == pattern[g + m - 1 - f])
                --g;
            suff[i] = f - g;
        }
    }
}

void PreBmGs(char *pattern, int m, int bmGs[]) //pattern右移的距离则要借助bmGs数组,下标是数字而不是字符, bmGs[j]表示pattern数组中j位置判断错误后应右移的距离
{
    int i, j, suff[SIZE];
    suffix(pattern, m, suff);

    for (i = 0; i < m; i++)
    {
        bmGs[i] = m;
    }
    /* 
    为什么从后往前，也就是i从大到小？原因在于如果i,j(i>j)位置同时满足第二种情况，那么m-1-i<m-1-j，
    而第63行代码保证了每个位置最多只能被修改一次，故而应该赋值为m-1-i
    */
    j = 0;
    for (i = m - 1; i >= 0; i--)
    {
        if (suff[i] == i + 1)
        {
            for (; j < m - 1 - i; j++)
            {
                if (bmGs[j] == m) //63
                    bmGs[j] = m - 1 - i;
            }
        }
    }
    /*
    为什么顺序从前到后呢，也就是i从小到大？
    原因在于如果suff[i]==suff[j]，i<j，那么m-1-i>m-1-j,我们应该取后者作为bmGs[m - 1 - suff[i]]的值。
    */
    for (i = 0; i < m - 1; i++)
    {
        bmGs[m - 1 - suff[i]] = m - 1 - i;
    }
}
int BoyerMoore(char *pattern, int m, char *text, int n)
{
    int i, j, bmBc[LENG256], bmGs[SIZE];

    // Preprocessing
    PreBmBc(pattern, m, bmBc);
    PreBmGs(pattern, m, bmGs);

    // Searching
    j = 0;
    while (j <= n - m)
    {
        for (i = m - 1; i >= 0 && pattern[i] == text[i + j]; i--)
            ;
        if (i < 0)
        {
            //printf("Find it, the position is %d\n", j);
            return j;
            //j += bmGs[0];
        }
        else
        {
            j += ((bmBc[text[i + j]] - m + 1 + i) > bmGs[i]) ? bmBc[text[i + j]] - m + 1 + i : bmGs[i];
        }
    }
    return -1;
    //printf("No find.\n");
}
int main()
{
    char text[10000], pattern[10000];
    while (1)
    {
        scanf("%s%s", text, pattern);
        //if(text == 0 || pattern == 0) {}

        int ans = BoyerMoore(pattern, strlen(pattern), text, strlen(text));
        if (ans != -1)
            printf("%d\n", ans);
        else
            printf("No find.\n");
    }

    return 0;
}
//https://www.cnblogs.com/lanxuezaipiao/p/3452579.html
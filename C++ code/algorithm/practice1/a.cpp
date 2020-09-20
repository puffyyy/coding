#include <iostream>
#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <vector>
#include <stack>
#include <queue>

using namespace std;
int n;
char a[90], b[90];
void exchange(char a[], char b[], int n)
{
    int i;
    for (i = 0; i < n; i++)
        b[i] = a[n - i - 1];
}
void fun(char a[], char b[], bool flag_m)
{
    int i, m, n;
    char c[81], x[81], y[81];
    if (strlen(a) > strlen(b))
    {
        m = strlen(a);
        n = strlen(b);
        exchange(a, x, m);
        exchange(b, y, n);
    }
    else
    {
        n = strlen(a);
        m = strlen(b);
        exchange(b, x, m);
        exchange(a, y, n);
    }          //数组x为长字符串数 ,m为长字符串的长度
    int k = 0; //k代表最前面的0的个数
    for (i = m - 1; i >= 0; i--)
    {
        if (x[i] == '0')
            k++;
        else
            break;
    }
    m = m - k;
    int count = 0, num = 0, num1, num2; //count代表进位
    for (i = n; i < m; i++)
        y[i] = '0';
    for (i = 0; i < m; i++)
    {
        num1 = x[i] - 48;
        num2 = y[i] - 48;
        num = (num1 + num2 + count) % 10;
        c[i] = num + 48;
        count = (num1 + num2 + count) / 10;
    }
    if (flag_m)
        printf("-");
    if (count == 1) //若一直进位，最终最高位是1
        printf("1");
    for (i = m; i >= 0; i--) //反序输出
    {
        if (c[i] >= '0' && c[i] <= '9')
            printf("%c", c[i]);
    }
    cout << endl;
}
void Int2String(long long n, char s[])
{
    int i = 0;
    if (n < 0)
        s[i++] = '-';
    n = (unsigned long long)(-n);

    while (n)
    {
        s[i++] = n % 10 + '0';
        n = n / 10;
    }
    s[i] = '\0';
}
long long String2Int(char *str) //字符串转数字
{
    char flag = '+'; //指示结果是否带符号
    long long res = 0;

    if (*str == '-') //字符串带负号
    {
        ++str;      //指向下一个字符
        flag = '-'; //将标志设为负号
    }
    //逐个字符转换，并累加到结果res
    while (*str >= 48 && *str <= 57)
    {
        res = 10 * res + *str++ - 48;
    }
    if (flag == '-') //处理是负数的情况
    {
        res = -res;
    }
    return res;
}
void sub(char s[], char c[])
{
    long long a = String2Int(s);
    long long b = String2Int(c);
    cout << a + b << endl;
}
int main()
{
    cin >> n;
    while (n--)
    {
        scanf("%s %s", a, b);
        if (*a == '0' && *b == '0')
            cout << '0' << endl;
        else if (*a == '0')
            cout << b << endl;
        else if (*b == '0')
            cout << a << endl;
        else if (*a != '-' && *b != '-')
            fun(a, b, 0);
        else if (*a == '-' && *b != '-')
            sub(b, a);
        else if (*b == '-' && *a != '-')
            sub(a, b);
        else
        {
            fun(a + 1, b + 1, 1);
        }
    }

    return 0;
}
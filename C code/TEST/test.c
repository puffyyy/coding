#include <stdio.h>

int readint()
{
    int p = 0, f = 1;
    char c = getchar();
    while (c < 48 || c > 57)
    {
        if (c == '-')
            f = -1;
        c = getchar();
    } //过滤无效字符,同时检查有没有负号
    while (c >= 48 && c <= 57)
        p = (p << 1) + (p << 3) + c - 48, c = getchar(); //开始读入整数
    return p * f;
}
int main()
{
    int a, b, c;
    int x, y;
    int t;
    t = readint();
    while (t--)
    {
        int cnt = 0;
        x = readint(), y = readint();
        if (x > y)
        {
            int tmp = x;
            x = y, y = tmp;
        }
        a = b = c = x;
        while (a < y || b < y || c < y)
        {
            if (a <= b && a <= c)

                if (b + c - 1 < y)
                    a = b + c - 1;
                else
                    a = y;

            else if (b <= a && b <= c)

                if (a + c - 1 < y)
                    b = a + c - 1;
                else
                    b = y;
            else
            {
                if (a + b - 1 < y)
                    c = a + b - 1;
                else
                    c = y;
            }
            cnt++;
        }
        printf("%d\n", cnt);
    }

    return 0;
}

#include <stdio.h>
int main()
{
    int a, b, c;
    int weigh = 0;
    while (~scanf("%d%d%d", &a, &b, &c))
    {
        if (a == b && b == c && c == 0)
        {
            printf("105\n");
            continue;
        }
        for (int i = 0;; i++)
        {
            weigh = i * 7 + c;
            if (weigh % 3 == a && weigh % 5 == b)
                break;
        }
        printf("%d\n", weigh);
    }
    return 0;
}
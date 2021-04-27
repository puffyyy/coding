
#include <stdio.h>
int array[11];
void rank(int m, int n)
{
    int i, j;
    if (m == n + 1)
    {
        for (i = 1; i <= n; i++)
            printf("%d ", array[i]);
        putchar('\n');
        return;
    }
    else
    {
        for (i = 1; i <= n; i++)
        {
            int k = 1;
            for (j = 1; j < m; j++)
            {
                if (array[j] == i)
                    k = 0;
            }
            if (k)
            {
                array[m] = i;
                rank(m + 1, n);
            }
        }
    }
}
int main()
{
    int t;
    scanf("%d", &t);
    rank(1, t);
    return 0;
}
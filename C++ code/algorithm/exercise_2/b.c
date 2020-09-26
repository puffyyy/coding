#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
int a[122][6];
int main()
{
    int i, j, k, n, cnt;
    int year;
    char ch[6];
    scanf("%d", &n);
    while (n--)
    {
        scanf("%d", &year);
        scanf("%s", ch);
        switch (ch[0])
        {
        case '1':
            ++a[year - 1900][0];
            break;
        case 'A':
            ++a[year - 1900][1];
            break;
        case 'C':
            ++a[year - 1900][2];
            break;
        case 'E':
            ++a[year - 1900][3];
            break;
        case 'I':
            ++a[year - 1900][4];
            break;
        case 'N':
            ++a[year - 1900][5];
            break;
        }
    }
    for (i = 120; i >= 0; --i)
    {
        for (j = 0; j < 6; ++j)
        {
            for (k = 0; k < a[i][j]; k++)
            {
                printf("%d ", i + 1900);
                switch (j)
                {
                case 0:
                    printf("1CLR\n");
                    break;
                case 1:
                    printf("AAA1\n");
                    break;
                case 2:
                    printf("CVP2\n");
                    break;
                case 3:
                    printf("E33V\n");
                    break;
                case 4:
                    printf("ICM1\n");
                    break;
                case 5:
                    printf("NIP5\n");
                    break;
                }
            }
        }
    }
    return 0;
}

/*
5
2017 1CLR
2016 1CLR
2016 AAA1
2017 AAA1
2017 1CLR
*/
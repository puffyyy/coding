#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
FILE *fout;
int main()
{
    fout = fopen("in.txt", "w");
    int n = 1, m = 2;
    srand((unsigned)time(NULL));

    m = rand() % 1000;
    n = rand() % 1000;
    fprintf(fout, "1\n");
    fprintf(fout, "%d %d\n", n, m);
    for (int i = 0; i < n; i++)
    {
        for (int i = 0; i < n; i++)
        {
            int l;
            l = rand() % 1000000;
            fprintf(fout, "%d ", l);
        }
        fprintf(fout, "\n");
    }
    fclose(fout);
    return 0;
}
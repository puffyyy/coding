#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
FILE *fout;
int main()
{
    fout = fopen("in.txt", "w");
    int n = 1, k = 2;
    srand((unsigned)time(NULL));

    k = rand() % 1000;
    n = rand() % 1000;

    fprintf(fout, "%d %d\n", n, k);
    for (int i = 0; i < n; i++)
    {
        int l, v;
        l = rand() % 1000000;
        v = rand() % 1000000;
        fprintf(fout, "%d %d\n", l, v);
    }
    fclose(fout);
    return 0;
}
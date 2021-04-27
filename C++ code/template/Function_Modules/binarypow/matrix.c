#include <stdio.h>
#include <stdlib.h>
struct matrix
{
    int mat[20][20];
};

struct matrix mul(struct matrix x, struct matrix y, int size)
{ //矩阵乘法
    struct matrix tmp;
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            tmp.mat[i][j] = 0;
            for (int k = 0; k < size; k++)
            {
                tmp.mat[i][j] += (x.mat[i][k] * y.mat[k][j]);
            }
            tmp.mat[i][j] = tmp.mat[i][j];
        }
    }
    return tmp;
}
struct matrix matrix_pow(struct matrix x, struct matrix *res, int n, int size)
{
    for (int i = 0; i < size; i++)
        res->mat[i][i] = 1;
    while (n)
    {
        if (n & 1)
            *res = mul(*res, x, size);
        *res = mul(*res, *res, size);
        n >>= 1;
    }
    return *res;
}
int main()
{
    struct matrix a, b;
    for (int i = 0; i < 2; i++)
        for (int j = 0; j < 2; j++)
            a.mat[i][j] = j + 1;
    for (int i = 0; i < 2; i++)
        for (int j = 0; j < 2; j++)
            b.mat[i][j] = 0;
    matrix_pow(a, &b, 2, 2);
    for (int i = 0; i < 2; i++)
        for (int j = 0; j < 2; j++)
            printf(j == 1 ? "%d\n" : "%d ", b.mat[i][j]);

    return 0;
}
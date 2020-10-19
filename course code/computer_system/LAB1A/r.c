#include <stdio.h>
int b[64];
void convert_to_binary(int n, int b[])
{
    int pos = -1;
    for (int i = 1; i <= 32; i++)
    {
        b[++pos] = n & 1;
        n >>= 1;
    }
    for (int i = pos; i >= 0; i--)
        putchar('0' + b[i]);
    putchar('\n');
}
int main()
{
    int n;
    scanf("%d", &n);
    convert_to_binary(n, b);
    printf("%x\n", n);
    return 0;
}
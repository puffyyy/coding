#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

typedef unsigned packed_t;
/* Extract byte from word. Return as signed integer */
int xbyte(packed_t word, int bytenum);
/* Failed attempt at xbyte */
int xbyte(packed_t word, int bytenum)
{
    return (word >> ((bytenum) << 3)) & 0xFF;
}
int c_xbyte(packed_t word, int bytenum)
{
    return (int)((word << ((3 - bytenum) << 3))) >> 24;
}
void showbinary(int a, int f)
{
    if (f == 33)
        return;
    showbinary(a >> 1, f + 1);
    printf("%d", a & 1);
}
int main()
{
    unsigned a = 0xff;
    showbinary(a, 1);
    for (int i = 0; i < 4; i++)
        printf("%d ", c_xbyte(a, i));
    putchar('\n');
    showbinary(c_xbyte(a, 0), 1);
    for (int i = 0; i < 4; i++)
        printf("%d ", xbyte(a, i));
    showbinary(xbyte(a, 0), 1);
    return 0;
}
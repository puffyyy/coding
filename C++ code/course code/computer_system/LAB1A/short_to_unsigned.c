#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

int main()
{
    short sx;
    sx = -12345;
    printf("short sx: %d \n", sx);
    unsigned ui_sx = sx;
    printf("short to unsigned: %u \n", ui_sx);

    printf("change size:%d change unsigned: %u\n", (int)sx, (unsigned)(int)sx);

    printf("change unsigned: %u change size:%u\n", (unsigned short)sx, (unsigned)(unsigned short)sx);
    return 0;
}
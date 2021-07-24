
#include <stdio.h>

int main()
{
    int a = 1, b = 2, c = 0;
    asm(
        "addl %2, %0"    // 1
        : "=g"(c)        // 2
        : "0"(a), "g"(b) // 3
        : "memory");     // 4
    printf("c:%d\n", c);
    return 0;
}
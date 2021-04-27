#include <stdio.h>
#include <string.h>
struct
{
    int x;
    char *y;
} * p, A[] = {
           0, "for",
           5, "while",
           10, "do_while",
           15, "switch"};
int main()
{
    int i;
    p = A;
    printf("%d\n", ++p->x);    // ++操作符 优先级 低于 ->   先p->x 再将该值 ++ 再将该值保存后 输出 p=A[0]
    printf("%d\n", ++(p->x));  //加() 不改变顺序 同上 p=A[0]
    printf("%d\n", (p++)->x);  // (p++) 操作 先return p 即执行输出 p->x 操作 结束后 p++ 此时 p=A[1];
    printf("%d\n", p++->x);    //同上
    printf("%c\n", *p->y);     //p=A[2]
    printf("%c\n", *p->y++);   //(p->y)表示字符串数组  (p->y)++先执行 return p->y  再执行*(p->y) 最后(p->y)字符串指针++ 右移
    printf("%c\n", *(p->y++)); //执行顺序同上
    printf("%c\n", *p++->y);
    for (i = 0; i < 4; i++)
        printf("%d, % s\n", A[i].x, A[i].y);
    return 0;
}
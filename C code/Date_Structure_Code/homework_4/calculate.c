#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#define MAXSIZE 201
typedef int dataType;
enum oper
{
    EQU,
    ADD,
    MIN,
    MUL,
    DIV,
    MOD,
    LEFT,
    RIGHT
};
enum symbol
{
    NUM,
    OP,
    EQ,
    OTHER
};
int PRI[] = {-1, 0, 0, 1, 1, 1, 2, 2};
union sym {
    dataType num;
    enum oper op;
};
dataType numStack[MAXSIZE];
int nTop = -1;
enum oper opStack[MAXSIZE];
int oTop = -1;
enum symbol getSym(union sym *item);
void operate(enum oper op);
void compute(enum oper op);
void pushNum(dataType num);
dataType popNum();
void pushOp(enum oper op);
enum oper popOp();
enum oper topOp();
int main()
{
    union sym item;
    enum symbol s;
    while ((s = getSym(&item)) != EQ)
    {
        if (s == NUM)
            pushNum(item.num);
        else if (s == OP)
            operate(item.op);
        else
            continue;
    }
    while (oTop >= 0)
        compute(popOp());
    if (nTop == 0)
        printf("%d\n", popNum());
    return 0;
}
enum symbol getSym(union sym *item)
{
    int c, n;
    while ((c = getchar()) != '=')
    {
        if (c >= '0' && c <= '9')
        {
            for (n = 0; c >= '0' && c <= '9'; c = getchar())
                n = n * 10 + c - '0';
            ungetc(c, stdin);
            item->num = n;
            return NUM;
        }
        else
            switch (c)
            {
            case '+':
                item->op = ADD;
                return OP;
            case '-':
                item->op = MIN;
                return OP;
            case '*':
                item->op = MUL;
                return OP;
            case '/':
                item->op = DIV;
                return OP;
            case '%':
                item->op = MOD;
                return OP;
            case '(':
                item->op = LEFT;
                return OP;
            case ')':
                item->op = RIGHT;
                return OP;
            case ' ':
            case '\t':
            case '\n':
                break; //重新读入字符
            default:
                return OTHER;
            }
    }
    return EQ;
}
void operate(enum oper op)
{
    enum oper t;
    if (op != RIGHT)
    {
        while (PRI[op] <= PRI[topOp()] && topOp() != LEFT)
        {
            compute(popOp());
        }
        pushOp(op);
    }
    else
        while ((t = popOp()) != LEFT)
            compute(t);
}
void compute(enum oper op)
{
    dataType tmp;
    switch (op)
    {
    case ADD:
        pushNum(popNum() + popNum());
        break;
    case MIN:
        tmp = popNum();
        pushNum(popNum() - tmp);
        break;
    case MUL:
        pushNum(popNum() * popNum());
        break;
    case DIV:
        tmp = popNum();
        pushNum(popNum() / tmp);
        break;
    case MOD:
        tmp = popNum();
        pushNum(popNum() % tmp);
        break;
    }
}
/*数据栈*/
void pushNum(dataType num)
{
    if (nTop == MAXSIZE - 1)
    {
        printf("data stack is full!\n");
    }
    numStack[++nTop] = num;
}
dataType popNum()
{
    if (nTop == -1)
    {
        printf("error in the expression!\n");
    }
    return numStack[nTop--];
}
/*运算符栈*/
void pushOp(enum oper op)
{
    if (oTop == MAXSIZE - 1)
    {
        printf("operator stack is full!\n");
    }
    opStack[++oTop] = op;
}
enum oper topOp()
{
    if (oTop == -1)
        return 0;
    return opStack[oTop];
}
enum oper popOp()
{
    if (oTop != -1)
    {
        return opStack[oTop--];
    }
    return EQU;
}
/*

24 / ( 1 + 5%3 + 36 / 6 / 2 - 2) * ( 12 / 2 / 2 )     =

*/
#include <stdio.h>
#include <stdlib.h>
#define MAXSIZE 101
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
union sym {
    int num;
    enum oper op;
};
enum symbol
{
    NUM,
    OP,
    END,
    OTHER
};
int PRI[] = {-1, 0, 0, 1, 1, 1, 2, 2};
/************** stack **************/
enum oper stack[MAXSIZE];
int TOP = -1;
int isempty()
{
    return TOP == -1;
}
void push(enum oper x)
{
    stack[++TOP] = x;
}
enum oper top()
{
    return stack[TOP];
}
enum oper pop()
{
    return stack[TOP--];
}
/***************** ******************/
enum symbol getSym(union sym *item, char infix[], int *i)
{
    int c, n;
    while ((c = infix[*i]) != '\0')
    {
        if (c >= '0' && c <= '9')
        {
            for (n = 0; c >= '0' && c <= '9'; c = infix[++(*i)])
                n = n * 10 + c - '0';
            *i--;
            item->num = n;
            return NUM;
        }
        else
        {
            ++*i;
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
                break;
            default:
                return OTHER;
            }
        }
    }
    return END;
}

char op_to_c(enum oper op)
{
    switch (op)
    {
    case ADD:
        return '+';
        break;
    case MIN:
        return '-';
        break;
    case MUL:
        return '*';
        break;
    case DIV:
        return '/';
        break;
    case MOD:
        return '%';
        break;
    }
    return -1;
}

void transfer_infix_to_postfix_expression(char infix[], char post[])
{
    union sym item;
    enum symbol s;
    enum oper t;
    int postpos = 0, infixpos = 0;
    while ((s = getSym(&item, infix, &infixpos)) != END)
    {
        if (s == NUM)
        {
            int lenth = 0;
            int temp, n = item.num;
            char a[10];
            while (n != 0)
            {
                temp = n % 10;
                n /= 10;
                a[lenth++] = temp + '0';
            }
            for (lenth--; lenth >= 0; lenth--)
            {
                post[postpos++] = a[lenth];
            }
            post[postpos++] = ' ';
        }
        else if (s == OP)
        {
            if (item.op != RIGHT)
            {
                while (PRI[item.op] <= PRI[top()] && top() != LEFT)
                {
                    post[postpos++] = op_to_c(pop());
                }
                push(item.op);
            }
            else
                while ((t = pop()) != LEFT)
                    post[postpos++] = op_to_c(t);
        }
    }
    while (!isempty())
    {
        post[postpos++] = op_to_c(pop());
    }
    post[postpos++] = '\0';
}
int compute_postfix_expression(char post[])
{
    union sym item;
    enum symbol s;
    int numstack[MAXSIZE], numtop = -1;
    int postpos = 0;
    while ((s = getSym(&item, post, &postpos)) != END)
    {
        if (s == NUM)
        {
            numstack[++numtop] = item.num;
        }
        else if (s == OP)
        {
            int fir, sec;
            sec = numstack[numtop--];
            fir = numstack[numtop--];
            switch (op_to_c(item.op))
            {
            case '+':
                numstack[++numtop] = fir + sec;
                break;
            case '-':
                numstack[++numtop] = fir - sec;
                break;
            case '*':
                numstack[++numtop] = fir * sec;
                break;
            case '/':
                numstack[++numtop] = fir / sec;
                break;
            case '%':
                numstack[++numtop] = fir % sec;
                break;
            default:
                break;
            }
        }
    }
    return numstack[0];
}

int main()
{
    char infix[MAXSIZE], postfix[MAXSIZE];
    gets(infix);
    transfer_infix_to_postfix_expression(infix, postfix);
    puts(postfix);
    int ans = compute_postfix_expression(postfix);
    printf("%d", ans);
    return 0;
}
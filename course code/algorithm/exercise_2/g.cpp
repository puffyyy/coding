#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <cstdlib>
using namespace std;

char name[5] = {'b', 'g', 'r', 'y'};
void place(char ch, int x, int y)
{
    switch (ch)
    {
    case 'b':
        printf("b (%d,%d) (%d,%d) (%d,%d)\n", x + 1, y, x, y + 1, x + 1, y + 1);
        break;
    case 'g':
        printf("g (%d,%d) (%d,%d) (%d,%d)\n", x - 1, y, x - 1, y + 1, x, y + 1);
        break;
    case 'r':
        printf("r (%d,%d) (%d,%d) (%d,%d)\n", x, y - 1, x + 1, y - 1, x + 1, y);
        break;
    case 'y':
        printf("y (%d,%d) (%d,%d) (%d,%d)\n", x - 1, y - 1, x, y - 1, x - 1, y);
        break;
    }
}
void devide(int x, int y, int x0, int y0, int x1, int y1)
{
    if (x0 == x1)
        return;
    int x_ = (x1 + x0) / 2, y_ = (y1 + y0) / 2;
    if (x <= x_)
    {
        if (y <= y_) //左上
        {
            place('b', x_, y_);
            devide(x, y, x0, y0, x_, y_);
            devide(x_, y_ + 1, x0, y_ + 1, x_, y1);
            devide(x_ + 1, y_, x_ + 1, y0, x1, y_);
            devide(x_ + 1, y_ + 1, x_ + 1, y_ + 1, x1, y1);
        }
        else //左下
        {
            place('r', x_, y_ + 1);
            devide(x_, y_, x0, y0, x_, y_);                 //左上
            devide(x, y, x0, y_ + 1, x_, y1);               //左下
            devide(x_ + 1, y_, x_ + 1, y0, x1, y_);         //右上
            devide(x_ + 1, y_ + 1, x_ + 1, y_ + 1, x1, y1); //右下
        }
    }
    else
    {
        if (y <= y_) //右上
        {
            place('g', x_ + 1, y_);
            devide(x_, y_, x0, y0, x_, y_);                 //左上
            devide(x_, y_ + 1, x0, y_ + 1, x_, y1);         //左下
            devide(x, y, x_ + 1, y0, x1, y_);               //右上
            devide(x_ + 1, y_ + 1, x_ + 1, y_ + 1, x1, y1); //右下
        }
        else //右下
        {
            place('y', x_ + 1, y_ + 1);
            devide(x_, y_, x0, y0, x_, y_);         //左上
            devide(x_, y_ + 1, x0, y_ + 1, x_, y1); //左下
            devide(x_ + 1, y_, x_ + 1, y0, x1, y_); //右上
            devide(x, y, x_ + 1, y_ + 1, x1, y1);   //右下
        }
    }
}
int main()
{
    int n;
    int x, y;
    cin >> n >> x >> y;
    if ((n * n - 1) % 3 != 0)
    {
        printf("None\n");
        return 0;
    }
    devide(x, y, 0, 0, n - 1, n - 1);

    return 0;
}
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#define Delta 0.00001
#define Alpha 1.3
#define Epsilon 0.00001
#define N 2
#define K (2 * N)

int times;
struct Point
{
    double x, y;
    double val;
} * _good, *_bad, *_2ndbad, _medium, _reflect, _extand, shape_complex[4], upper_boundary, lower_boundary;
double alpha = Alpha;
double beta = 2.0;
int cmp_point_value(const void *a, const void *b)
{
    struct Point *c = (struct Point *)a;
    struct Point *d = (struct Point *)b;
    return c->val - d->val;
}
double F(double x1, double x2)
{
    double val;
    // val = x1 * x1 + x2 * x2 + 5;
    // val = exp(x1) * (4 * x1 * x1 + 2 * x2 * x2 + 4 * x1 * x2 + 2 * x2 + 1);
    val = ((2 * x1 + x2) * (2 * x1 + x2) + (x2 + 1) * (x2 + 1)) * exp(x1);
    return val;
}
double calP(struct Point *p)
{
    p->val = F(p->x, p->y);
    return p->val;
}
void init()
{
    lower_boundary.x = -10000, lower_boundary.y = -10000;
    upper_boundary.x = 10000, upper_boundary.y = 10000;
    shape_complex[0].x = -1;
    shape_complex[0].y = 1; //5
    calP(shape_complex + 0);
}
struct Point rand_point()
{
    struct Point p;
    p.x = rand() / (RAND_MAX + 1.0) * (upper_boundary.x - lower_boundary.x) + lower_boundary.x;
    p.y = rand() / (RAND_MAX + 1.0) * (upper_boundary.y - lower_boundary.y) + lower_boundary.y;
    calP(&p);
    return p;
}
int is_convergent()
{
    return fabs(shape_complex[0].val - shape_complex[3].val) < Epsilon || (fabs(shape_complex[0].val - shape_complex[3].val) / fabs(shape_complex[0].val)) < Epsilon;
    //  || distance < eps
}
int is_in_region(struct Point p)
{
    return p.x < upper_boundary.x && p.x > lower_boundary.x && p.y < upper_boundary.y && p.y > lower_boundary.y;
}
void generate_shape_complex()
{
    for (int i = 1; i < K; i++)
    {
        shape_complex[i] = rand_point();
    }
}
void sort_shape_complex() //good 0 bad 3 second_bad 2
{
    times += 1;
    qsort(shape_complex, K, sizeof(struct Point), cmp_point_value);
    _bad = shape_complex + K - 1;
    _good = shape_complex;
    _2ndbad = shape_complex + K - 2;
    if (is_convergent())
    {
        printf("x=%.6lf\ny=%.6lf\nval=%.6lf\n", _good->x, _good->y, _good->val);
        system("pause");
        exit(0);
    }
    printf("time:%d good\nx=%.6lf\ny=%.6lf\nval=%.6lf\n", times, _good->x, _good->y, _good->val);
    printf("time:%d bad\nx=%.6lf\ny=%.6lf\nval=%.6lf\n", times, _bad->x, _bad->y, _bad->val);
}
void cal_midium_point()
{
    _medium.x = 0;
    _medium.y = 0;
    for (int i = 0; i < K - 1; i++)
    {
        _medium.x += shape_complex[i].x;
        _medium.y += shape_complex[i].y;
    }
    _medium.x /= (K - 1);
    _medium.y /= (K - 1);
    calP(&_medium);
}
void cal_reflect_point()
{
    _reflect.x = _medium.x + alpha * (_medium.x - _bad->x);
    _reflect.y = _medium.y + alpha * (_medium.y - _bad->y);
    calP(&_reflect);
}
void cal_extand_point()
{
    _extand.x = _medium.x + beta * (_reflect.x - _medium.x);
    _extand.y = _medium.y + beta * (_reflect.y - _medium.y);
    calP(&_extand);
}
void Iterate()
{
    init();
    generate_shape_complex();
step_4:
    sort_shape_complex();
step_5:
    cal_midium_point();
step_6:
    cal_reflect_point();
    if (is_in_region(_reflect))
    {
        if (_reflect.val < _2ndbad->val)
        {
            if (_reflect.val < _good->val)
            {
            cal_extand:
                cal_extand_point();
                if (!is_in_region(_extand))
                {
                    *_bad = _reflect;
                    goto step_4;
                }
                else
                {
                    if (_extand.val < _reflect.val)
                    {
                        _reflect = _extand;
                        goto cal_extand;
                    }
                    else
                    {
                        *_bad = _reflect;
                        goto step_4;
                    }
                }
            }
            else
            {
                *_bad = _reflect;
                goto step_4;
            }
        }
        else
        {
            if (_reflect.val < _bad->val)
            {
                *_bad = _reflect;
                goto step_4;
            }
            else
            {
                goto reduce;
            }
        }
    }
    else
    {
    reduce:
        if (alpha < Delta)
        {
            struct Point p; //swap
            p = *_bad;
            *_bad = *_2ndbad;
            *_2ndbad = p;
            goto step_5;
        }
        else
        {
            alpha /= 2;
            goto step_6;
        }
    }
}

int main()
{
    Iterate();
    system("pause");
    return 0;
}

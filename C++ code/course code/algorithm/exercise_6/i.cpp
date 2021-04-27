#include <iostream>
#include <algorithm>
#include <cmath>
#include <cstring>
#define MAXN 400010 //2 *（m+n）
using namespace std;
const double Pi = acos(-1.0);
char A[MAXN], B[MAXN];
struct complex
{
    double x, y;
    complex(double xx = 0, double yy = 0)
    {
        x = xx, y = yy;
    }
} a[MAXN], b[MAXN];
complex operator+(complex a, complex b)
{
    return complex(a.x + b.x, a.y + b.y);
}
complex operator-(complex a, complex b)
{
    return complex(a.x - b.x, a.y - b.y);
}
complex operator*(complex a, complex b)
{
    return complex(a.x * b.x - a.y * b.y, a.x * b.y + b.x * a.y);
}
int N, M;
int l, r[MAXN];
int limit;
int ans[MAXN << 1];
inline void init()
{
    memset(r, 0, sizeof(r));
    limit = 1;
    l = 0;
    for (int i = 0; i < MAXN; ++i)
        a[i].x = a[i].y = b[i].x = b[i].y = 0.0;
}
inline void FFT_Iteration(complex *C, double type)
{
    for (int i = 0; i < limit; ++i)
        if (i < r[i])
            swap(C[i], C[r[i]]);
    for (int mi = 1; mi < limit; mi <<= 1)
    {
        int len = mi << 1;
        complex Wn(cos(Pi / mi), type * sin(Pi / mi));
        for (int j = 0; j < limit; j += len)
        {
            complex w(1, 0);
            for (int k = 0; k < mi; ++k, w = w * Wn)
            {
                complex x = C[j + k], y = w * C[j + mi + k];
                C[j + k] = x + y;
                C[j + mi + k] = x - y;
            }
        }
    }
}
inline void getLimitRev()
{
    while (limit <= N + M)
        limit <<= 1, ++l;
    for (int i = 0; i < limit; ++i)
    {
        r[i] = (r[i >> 1] >> 1) | ((i & 1) << (l - 1));
    }
}
inline void cal_Poly(char scissor, char storn)
{
    init();
    for (int i = 0; i <= N; ++i)
        if (A[i] == scissor)
            a[i].x = 1;
    for (int i = 0; i <= M; ++i)
        if (B[i] == storn)
            b[i].x = 1;
    getLimitRev();
    FFT_Iteration(a, 1);
    FFT_Iteration(b, 1);
    for (int i = 0; i <= limit; ++i)
        a[i] = a[i] * b[i];
    FFT_Iteration(a, -1);
    for (int i = 0; i <= N + M; ++i)
    {
        ans[i] += (int)(a[i].x / limit + 0.5);
    }
}
int main()
{
    memset(ans, 0, sizeof(ans));
    scanf("%d%d", &N, &M);
    scanf("%s%s", A, B);
    reverse(B, B + M);
    cal_Poly('P', 'S');
    cal_Poly('S', 'R');
    cal_Poly('R', 'P');
    int mm = -1;
    for (int i = M - 1; i < N + M - 1; ++i)
    {
        mm = max(mm, ans[i]);
    }
    printf("%d", mm);
    return 0;
}
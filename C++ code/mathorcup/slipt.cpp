#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include <stack>
#include <time.h>
#include <set>
using namespace std;
typedef long long ll;
const int MS = 1e5 + 5;
struct OrderStruct
{
    double lenth, width;
    int cnt;
    int rate;
} Order[20];
struct RawStruct
{
    double lenth, width;
    int cnt;
} Raw[20];
int now = 1;
int step = 4;
int cnt[20];

int vec[20][20]; //以第a的订单为主的 方式， 订单b 切了val块
double remain[20];
void recur(int no, double curlen, int a[10])
{
    if (Raw[now].lenth - curlen < 0)
        return;
    if (no >= 10 || Raw[now].lenth - curlen - Order[no].lenth < 0)
    {
        int ma = 0;
        int nu = 0;
        for (int i = 0; i < no; i++)
        {
            if (ma < a[i])
            {
                ma = a[i], nu = i;
            }
        }
        if (remain[nu] > Raw[now].lenth - curlen)
        {
            for (int i = 0; i < no; i++)
                vec[nu][i] = a[i];
            for (int i = no; i < 10; i++)
                vec[nu][i] = 0;
            remain[nu] = Raw[now].lenth - curlen;
        }
        // printf("%d %lf\n", no, );
        return;
    }
    for (int i = 0; i <= Order[no].cnt; i += step - 2 + int(rand()) % 5)
    {
        a[no] = i;
        recur(no + 1, curlen + i * Order[no].lenth, a);
    }
    return;
}
int main()
{
    srand(unsigned(time(0)));
    FILE *rawfin = fopen("G:\\mathorCup\\Code\\Q2\\Raw.txt", "r");
    FILE *orderfin = fopen("G:\\mathorCup\\Code\\Q2\\OrderInfo.txt", "r");
    for (int i = 0; i <= 10; i++)
        fscanf(orderfin, "%lf%lf%d%d", &Order[i].lenth, &Order[i].width, &Order[i].cnt, &Order[i].rate);
    for (int i = 0; i <= 10; i++)
        fscanf(rawfin, "%lf%lf%d", &Raw[i].lenth, &Raw[i].width, &Raw[i].cnt);
    for (now = 7; now < 10; now++)
    {
        string outpath = "G:\\mathorCup\\Code\\Q2\\r" + to_string(now) + "s" + to_string(step) + ".txt";
        FILE *out = fopen(outpath.c_str(), "w");
        int a[10];
        for (int i = 0; i < 10; i++)
        {
            remain[i] = 0x3ffffff;
        }
        memset(vec, 0, sizeof(vec));
        recur(0, 0, a);
        for (int i = 0; i < 10; i++)
        {
            printf("Order %d: remain=%lf\n", i, remain[i]);
            for (int j = 0; j < 10; j++)
            {
                printf("%d: %d ", j, vec[i][j]);
            }
            printf("\n\n");
        }
        for (int i = 0; i < 10; i++)
        {
            fprintf(out, "%d: %.6lf\n", i, remain[i]);
            for (int j = 0; j < 10; j++)
            {
                fprintf(out, "%d ", vec[i][j]);
            }
            fprintf(out, "\n");
        }
        fclose(out);
    }
    return 0;
}
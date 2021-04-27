#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include <stack>
#include <queue>
#include <set>
using namespace std;
typedef long long int ll;
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
int now = 0;
int main()
{
    FILE *rawfin = fopen("G:\\mathorCup\\Code\\Q2\\Raw.txt", "r");
    FILE *orderfin = fopen("G:\\mathorCup\\Code\\Q2\\OrderInfo.txt", "r");
    for (int i = 0; i <= 10; i++)
        fscanf(orderfin, "%lf%lf%d%d", &Order[i].lenth, &Order[i].width, &Order[i].cnt, &Order[i].rate);
    for (int i = 0; i <= 10; i++)
        fscanf(rawfin, "%lf%lf%d", &Raw[i].lenth, &Raw[i].width, &Raw[i].cnt);
    double tmp = Raw[now].lenth;
    int a[10] = {16, 16, 4, 12, 20, 20, 16, 24, 0, 24};
    //
    //0 : 16 1 : 16 2 : 4 3 : 12 4 : 20 5 : 20 6 : 16 7 : 24 8 : 0 9 : 24 for (int i = 0; i < 10; i++);
    for (int i = 0; i < 10; i++)
    {
        tmp -= Order[i].lenth * a[i];
    }
    printf("\n%lf\n", tmp);
    return 0;
}
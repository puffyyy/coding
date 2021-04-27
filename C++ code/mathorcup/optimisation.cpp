#include <iostream> //取更优
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
int temp[20];
int map[10][10];
double minremain[10];
int whichRaw[10];
int now = 0;
int main()
{
    FILE *rawfin = fopen("G:\\mathorCup\\Code\\Q2\\Raw.txt", "r");
    FILE *orderfin = fopen("G:\\mathorCup\\Code\\Q2\\OrderInfo.txt", "r");
    for (int i = 0; i <= 10; i++)
    {
        fscanf(orderfin, "%lf%lf%d%d", &Order[i].lenth, &Order[i].width, &Order[i].cnt, &Order[i].rate);
    }
    for (int i = 0; i <= 10; i++)
    {
        fscanf(rawfin, "%lf%lf%d", &Raw[i].lenth, &Raw[i].width, &Raw[i].cnt);
    }
    int fileListnum[] = {0, 4, 5, 6, 9};
    for (int i = 0; i < 10; i++)
    {
        minremain[i] = 0x3ffffff;
    }
    for (int number : fileListnum)
    {
        string fileWidth = "G:\\mathorCup\\Code\\Q2\\width\\r" + to_string(number) + "s4width.txt";
        FILE *widthfin = fopen(fileWidth.c_str(), "r");
        for (int i = 0; i <= 10; i++)
        {
            int num;
            double tempremain;

            fscanf(widthfin, "%d%lf", &num, &tempremain);
            for (int j = 0; j < 10; j++)
                fscanf(widthfin, "%d", &temp[j]);
            if (minremain[i] > tempremain)
            {
                for (int j = 0; j < 10; j++)
                    map[i][j] = temp[j];
                minremain[i] = tempremain;
                whichRaw[i] = number;
            }
        }
        fclose(widthfin);
    }
    FILE *out = fopen("G:\\mathorCup\\Code\\Q2\\width\\optimisation1.txt", "w");
    for (int i = 0; i < 10; i++)
    {
        fprintf(out, "%d %d %lf\n", i, whichRaw[i], minremain[i]);
        for (int j = 0; j < 10; j++)
        {
            fprintf(out, "%d ", map[i][j]);
        }
        fprintf(out, "\n");
    }
    return 0;
}
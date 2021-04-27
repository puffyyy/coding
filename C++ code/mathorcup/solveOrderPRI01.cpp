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
typedef long long ll;
const int MS = 1e5 + 5;
int now = 9;
int nowsize;
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
struct scheme
{
    double re;
    int a[10];
    bool operator<(const scheme &a) const
    {
        return re < a.re;
    }
};
priority_queue<scheme, vector<scheme>> heap;
vector<vector<vector<int>>> vec(10);
vector<vector<double>> maxlenINvecrawsplit(10);
int count[10];
double cal_remain_in_len(int now, int no, int a[])
{
    double r = Raw[now].lenth;
    for (int i = 0; i < no; i++)
    {
        r -= maxlenINvecrawsplit[now][i] * a[i];
    }
    r *= Raw[now].width;
    return r;
}

void recur(int now, int no, double curlen, int a[10])
{
    if (curlen > Raw[now].lenth)
        return;
    if (no >= nowsize)
        return;
    if (curlen + maxlenINvecrawsplit[now].at(no) > Raw[now].lenth)
    {
        scheme sch;
        // sch.re = cal_remain_in_len(now, no, a);
        sch.re = (Raw[now].lenth - curlen) * Raw[now].width;
        for (int i = 0; i < no; i++)
            sch.a[i] = a[i];
        for (int i = no; i < 10; i++)
            sch.a[i] = 0;
        heap.push(sch);
        while (heap.size() > 15)
            heap.pop();
    }
    for (int i = 0; i < 20; i += 1)
    {
        a[no] = i;
        recur(now, no + 1, curlen + i * maxlenINvecrawsplit[now][no], a);
    }
}
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

    string fileWidth = "G:\\mathorCup\\Code\\Q2\\width\\optimisation1.txt";
    FILE *widthfin = fopen(fileWidth.c_str(), "r");
    for (int i = 0; i < 10; i++)
    {
        int num, tmp;
        int raw;
        double tempremain;
        vector<int> tvec;
        fscanf(widthfin, "%d%d%lf", &num, &raw, &tempremain);
        double maxl = -1;
        for (int j = 0; j < 10; j++)
        {
            fscanf(widthfin, "%d", &tmp);
            tvec.push_back(tmp);
            if (tmp > 0)
                maxl = max(maxl, Order[j].lenth);
        }
        vec[raw].push_back(tvec);
        maxlenINvecrawsplit[raw].push_back(maxl);
    }
    fclose(widthfin);

    double curLen = Raw[now].lenth;
    double curWid = Raw[now].width;
    nowsize = vec[now].size();
    int a[10];
    recur(now, 0, 0, a);
    while (heap.size() > 15)
        heap.pop();
    for (int i = 0; i < heap.size(); i++)
    {
        scheme tmp = heap.top();
        heap.pop();
        printf("%d %lf\n", i, tmp.re);
        for (int j = 0; j < 10; j++)
        {
            if (tmp.a[j] > 0)
            {
                printf("%d %d\n", j, tmp.a[j]);
                for (int k = 0; k < 10; k++)
                {
                    if (vec[now][j][k] > 0)
                    {
                        printf("    %d %d\n", k, vec[now][j][k]);
                    }
                }
                printf("\n");
            }
        }
        printf("\n\n");
    }
    return 0;
}
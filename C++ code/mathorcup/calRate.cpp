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
vector<vector<int>> mat;
void readfiledata()
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
    fclose(rawfin);
    fclose(orderfin);
}

int main()
{
    readfiledata();
    FILE *outcsv = fopen("G:\\mathorCup\\Code\\Q2\\schema\\schemadec.csv", "a");
    int now = 0;
    for (; now < 10; now++)
    {
        string sch_in = "G:\\mathorCup\\Code\\Q2\\schema\\" + to_string(now) + ".txt";
        FILE *sinfile = fopen(sch_in.c_str(), "r");
        double allArea = Raw[now].lenth * Raw[now].width;

        //read
        int tmi;
        double tmd;
        int cnt_model;
        int hash[10];
        char line[20];
        int order, ordercnt;
        int method_no = 0;
        while (fscanf(sinfile, "%d%lf", &tmi, &tmd) != -1)
        {
            double junk = allArea;
            memset(hash, 0, sizeof(hash));
            fgets(line, 20, sinfile);
            while (fgets(line, 20, sinfile))
            {
                if (line[0] == '\n')
                    break;
                sscanf(line, "%d%d", &tmi, &cnt_model);
                while (fgets(line, 20, sinfile))
                {
                    if (line[0] == '\n')
                        break;
                    sscanf(line, "%d%d", &order, &ordercnt);
                    hash[order] += ordercnt * cnt_model;
                }
            }
            int flag = 1;
            for (int i = 0; i < 10; i++)
            {
                junk -= Order[i].lenth * Order[i].width * hash[i];
                if (hash[i] > Order[i].cnt)
                {
                    flag = 0;
                    break;
                }
            }
            if (flag == 0)
                continue;

            fprintf(outcsv, "%d %d ", now, ++method_no);
            for (int i = 0; i < 10; i++)
            {
                fprintf(outcsv, "%d ", hash[i]);
            }
            fprintf(outcsv, "%lf\n", junk);
        }
        fclose(sinfile);
    }
    return 0;
}
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
const int MS = 1e3 + 5;
int N, M, T;
int store[MS];
struct g
{
    int time;
    int id;
    bool operator<(const g &p) const { return time < p.time; }
} list[MS];
int visit[MS];
int ceche[MS];
int main()
{
    cin >> N >> M >> T;
    for (int i = 0; i < M; i++)
    {
        scanf("%d%d", &list[i].time, &list[i].id);
    }

    sort(list, list + M);
    int curTime = 1;
    int id;
    for (int i = 0; i < M; i++)
    {
        if (list[i].time > T)
            break;
        if (list[i].time == curTime)
        {
            id = list[i].id;
            visit[id] = 1;
            if (store[id] > 0)
            {
                store[id] += 2;
            }
            else
                store[id] = 2;
            if (store[id] > 5)
                ceche[id] = 1;
        }
        else
        {
            int delt = list[i].time - curTime;
            for (int j = 1; j <= N; j++)
            {
                if (visit[j] == 1)
                {
                    store[j] -= (delt - 1);
                    if (store[j] < 0)
                        store[j] = 0;
                }
                else
                {
                    store[j] -= delt;
                    if (store[j] < 0)
                        store[j] = 0;
                }
            }
            for (int j = 1; j <= N; j++)
            {
                if (ceche[j] == 1 && store[j] <= 3)
                    ceche[j] = 0;
            }
            curTime = list[i].time;
            memset(visit, 0, sizeof(visit));
            id = list[i].id;
            visit[id] = 1;
            if (store[id] > 0)
            {
                store[id] += 2;
            }
            else
                store[id] = 2;
            if (store[id] > 5)
                ceche[id] = 1;
        }
    }
    int delt = T - curTime;
    if (delt >= 0)
    {
        for (int i = 1; i <= N; i++)
        {
            if (visit[i] == 1)
                store[i] -= delt;
            else
                store[i] -= (delt + 1);
        }
        for (int i = 1; i <= N; i++)
        {
            if (ceche[i] == 1 && store[i] <= 3)
                ceche[i] = 0;
        }
    }

    int cnt = 0;
    for (int i = 1; i <= N; i++)
    {
        if (ceche[i] == 1)
            cnt += 1;
    }
    printf("%d", cnt);
    return 0;
}

/*
2 6 6
1 1
5 2
3 1
6 2
2 1
6 2
*/
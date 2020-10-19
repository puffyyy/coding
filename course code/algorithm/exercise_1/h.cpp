#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include <stack>
#include <queue>
using namespace std;
#define INT_MAX 2147483647
int t;
void calc(vector<int> &a, vector<int> &b, vector<int> &c)
{
    for (int i = 0; i < a.size(); i++)
    {
        for (int j = 0; j < b.size(); j++)
        {
            int tmp = a[i] + b[j];
            c.push_back(tmp);
            tmp = a[i] - b[j];
            c.push_back(tmp);
            tmp = a[i] * b[j];
            c.push_back(tmp);
            if (b[j])
            {
                tmp = a[i] / b[j];
                c.push_back(tmp);
            }
        }
    }
    a.clear();
    b.clear();
}
int main()
{
    cin >> t;
    while (t--)
    {
        int num[5];
        int minans = INT_MAX;
        for (int i = 0; i < 4; i++)
            cin >> num[i];

        vector<int> first, mid, then, final;
        { //abcd
            first.push_back(num[0]);
            mid.push_back(num[1]);
            calc(first, mid, then);
            first.push_back(num[2]);
            calc(then, first, mid);
            first.push_back(num[3]);
            calc(mid, first, final);
            minans = min(*std::min_element(std::begin(final), std::end(final)), minans);
            final.clear();
        }
        {
            first.push_back(num[0]);
            mid.push_back(num[1]);
            calc(first, mid, then);
            first.push_back(num[2]);
            mid.push_back(num[3]);
            calc(first, mid, final);
            calc(then, final, first);
            minans = min(*std::min_element(std::begin(first), std::end(first)), minans);
            first.clear();
        }
        { // a bc    d
            first.push_back(num[1]);
            mid.push_back(num[2]);
            calc(first, mid, then);
            first.push_back(num[0]);
            calc(first, then, final);

            first.push_back(num[3]);
            calc(final, first, then);
            minans = min(*std::min_element(std::begin(then), std::end(then)), minans);
            then.clear();
        }
        {
            first.push_back(num[1]);
            mid.push_back(num[2]);
            calc(first, mid, then);
            first.push_back(num[3]);
            calc(then, first, mid);
            first.push_back(num[0]);
            calc(first, mid, final);
            minans = min(*std::min_element(std::begin(final), std::end(final)), minans);
            final.clear();
        }
        {
            first.push_back(num[2]);
            mid.push_back(num[3]);
            calc(first, mid, then);
            first.push_back(num[1]);
            calc(first, then, mid);
            first.push_back(num[0]);
            calc(first, mid, final);
            minans = min(*std::min_element(std::begin(final), std::end(final)), minans);
            final.clear();
        }
        cout << minans << endl;
    }

    return 0;
}
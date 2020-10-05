#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <math.h>
using namespace std;
int n, k, ans = 2;

int main()
{
    int t;
    cin >> t;
    while (t--)
    {
        int young = 2, adult = 0;
        cin >> n >> k;
        for (int i = 0; i < n; ++i)
        {

            adult += min(k, young); // grow up
            young -= min(k, young); // grow up
            young += adult >> 1;    // born
        }
        ans = adult + young;
        printf("%d\n", ans);
    }

    return 0;
}
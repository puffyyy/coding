#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
using namespace std;
typedef long long ll;
int a, b, c, T;
ll arr[50];
int main()
{
    cin >> a >> b >> c >> T;
    arr[33] = 1;
    for (int i = 34; i <= T + 32; i++)
    {
        arr[i] = arr[i - 1] + arr[i - a] - arr[i - a - b];
    }
    cout << arr[T + 32] - arr[T + 32 - a - b - c];
    return 0;
}
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <queue>
#include <map>
#include <cmath>
#include <cstring>
#include <cstdlib>
using namespace std;
typedef long long ll;
const int MS = 1e5 + 5;
int n;
vector<vector<int>> vec;
int ans = 0;
void recur(int no, int cur, int a[])
{
	if (cur == n && no == 10)
	{
		ans++;
		vector<int> tempv(a, a + 10);
		vec.push_back(tempv);
	}
	if (no >= 10)
		return;
	if (cur > n)
		return;
	for (int i = 1; i <= 3; i++)
	{
		a[no] = i;
		recur(no + 1, cur + i, a);
	}
}
int main()
{
	cin >> n;
	int a[10];
	recur(0, 0, a);
	cout << ans << endl;
	for (int i = 0; i < vec.size(); i++)
	{
		for (auto j : vec[i])
			cout << j << ' ';
		cout << endl;
	}
	return 0;
}

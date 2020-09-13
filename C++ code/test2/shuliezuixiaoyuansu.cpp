#include <iostream>
#include <queue>
#include <vector>
#include <functional>
#include <cstring>
#include <cstdio>
using namespace std;

int cnt = 1;
inline char xchar()
{
	static char buf[100000], *p1 = buf, *p2 = buf;
	return p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 100000, stdin), p1 == p2) ? EOF : *p1++;
}
inline long long xint()
{
	int s = 1, c = xchar();
	long long x = 0;
	while (c <= 32)
		c = xchar();
	if (c == '-')
		s = -1, c = xchar();
	for (; '0' <= c && c <= '9'; c = xchar())
		x = x * 10 + c - '0';
	return x * s;
}
void swap1(int &a, int &b)
{
	int tmp = b;
	b = a;
	a = tmp;
}
int quickSort(int a[], int left, int right)
{
	static int cnt = 0;
	if (left >= right)
		return 0;
	int i = left, j = left;
	for (i = left + 1; i <= right; i++)
	{
		if (a[i] < a[left])
			swap1(a[++j], a[i]);
	}
	swap1(a[left], a[j]);
	quickSort(a, left, j - 1);
	quickSort(a, j + 1, right);
	return cnt;
}
int main()
{
	long long tmp;
	int n;
	std::cin >> n;
	if (n == 0)
	{
		cout << '0';
		return 0;
	}
	int *array = new int[n];
	for (int i = 0; i < n; i++)
	{
		tmp = xint();
		array[i] = (int)tmp;
	}
	quickSort(array, 0, n - 1);
	for (int i = 1; i < n; i++)
	{
		if (array[i] == array[i - 1])
			continue;
		else
			++cnt;
	}
	cout << cnt;

	return 0;
}
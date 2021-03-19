#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>
#include <queue>
#include <map>
using namespace std;
int up(int i)
{
	if (i - 3 >= 0)
		return i - 3;
	else
		return -1;
}
int down(int i)
{
	if (i + 3 < 9)
		return i + 3;
	else
		return -1;
}
int left(int i)
{
	if (i % 3 == 0)
		return -1;
	else
		return i - 1;
}
int right(int i)
{
	if (i % 3 == 2)
		return -1;
	else
		return i + 1;
}
queue<string> q;
map<string, int> s;
string t = "1234567808";
int cnt = 0;
int bfs()
{
	int pos, z;
	string a, b;
	while (!q.empty())
	{
		cnt = max(cnt, (int)q.size());
		a = q.front();
		q.pop();
		z = a[9] - '0';
		if ((pos = up(z)) != -1)
		{
			b = a;
			swap(b[z], b[pos]);
			b[9] = pos + '0';
			if (!s.count(b))
				s[b] = s[a] + 1, q.push(b);
			if (b == t)
				return s[b];
		}
		if ((pos = down(z)) != -1)
		{
			b = a;
			swap(b[z], b[pos]);
			b[9] = pos + '0';
			if (!s.count(b))
				s[b] = s[a] + 1, q.push(b);
			if (b == t)
				return s[b];
		}
		if ((pos = left(z)) != -1)
		{
			b = a;
			swap(b[z], b[pos]);
			b[9] = pos + '0';
			if (!s.count(b))
				s[b] = s[a] + 1, q.push(b);
			if (b == t)
				return s[b];
		}
		if ((pos = right(z)) != -1)
		{
			b = a;
			swap(b[z], b[pos]);
			b[9] = pos + '0';
			if (!s.count(b))
				s[b] = s[a] + 1, q.push(b);
			if (b == t)
				return s[b];
		}
	}
	return -1;
}
int main()
{
	string a;
	cin >> a;
	int z;
	for (int i = 0; i < a.size(); i++)
	{
		if (a[i] == '0')
		{
			z = i;
			break;
		}
	}
	a += z + '0';
	q.push(a);
	s[a] = 0;
	cout << bfs();
	return 0;
}
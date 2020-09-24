#include <iostream>
#include <queue>
#include <vector>
#include <functional>
#include <cstring>
#include <cstdio>
using namespace std;

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

int main()
{

	return 0;
}
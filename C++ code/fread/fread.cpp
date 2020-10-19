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

char pbuf[1 << 20], *pp = pbuf;
inline void push(const char c)
{
	if (pp - pbuf == (1 << 20))
		fwrite(pbuf, 1, (1 << 20), stdout), pp = pbuf;
	*pp++ = c;
}

template <typename T>
inline void write(T x)
{
	static int sta[35];
	int top = 0;
	if (x < 0)
		push('-'), x = -x;
	do
	{
		sta[top++] = x % 10, x /= 10;
	} while (x);
	while (top)
		push(sta[--top] + '0');
	push('\n');
}

inline void writeint(int x)
{
	static int sta[35];
	int top = 0;
	do
	{
		sta[top++] = x % 10;
		x /= 10;
	} while (x);
	while (top)
		putchar(sta[--top] + '0');
}
int readint()
{
	int p = 0, f = 1;
	char c = getchar();
	while (c < 48 || c > 57)
	{
		if (c == '-')
			f = -1;
		c = getchar();
	} //过滤无效字符,同时检查有没有负号
	while (c >= 48 && c <= 57)
		p = (p << 1) + (p << 3) + c - 48, c = getchar(); //开始读入整数
	return p * f;
}
int main()
{

	fwrite(pbuf, 1, pp - pbuf, stdout);
	return 0;
}
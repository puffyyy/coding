#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define maxm 1000005
struct point
{
	double x;
	double y;
};
typedef struct point Node;
typedef struct point *Nodeptr;
Node a[maxm], s[maxm], b;
int m, n, k, color[maxm];
double xx, yy;

void find_tubao()
{
	int flag = 1, l;
	memset(color, 0, sizeof(color));
	int i, j;
	xx = a[1].x;
	yy = a[1].y;
	n = 1;
	for (i = 2; i <= m; i++) //�ҵ�ƽ������ߵĵ�,����͹���ĵ�һ����
	{
		if (a[i].x < xx)
		{
			yy = a[i].y;
			xx = a[i].x;
			n = i;
		}
		else if (a[i].x - xx > -0.000000001 && a[i].x - xx < 0.000000001 && a[i].y < yy)
		{
			yy = a[i].y;
			xx = a[i].x;
			n = i;
		}
	}
	k = 0;
	color[n] = 1;
	s[++k] = a[n];
	xx = 100000000;
	for (i = 1; i <= m; i++) //�ҵ����ڵ�һ���㼫����С�ĵ㣬��Ϊ�ڶ�����
	{
		if (color[i] == 0)
		{
			if ((a[i].y - b.y) / (a[i].x - b.x) < xx)
			{
				xx = (a[i].y - b.y) / (a[i].x - b.x);
				l = i;
			}
		}
	}
	color[l] = 1;
	s[++k] = a[l];
	while (flag == 1) //ÿ���ҵ�ת��Ƕ���С�ĵ�
	{
		xx = -100000000;
		for (i = 1; i <= m; i++)
		{
			yy = ((a[i].x - s[k].x) * (s[k].x - s[k - 1].x) + (a[i].y - s[k].y) * (s[k].y - s[k - 1].y)) / sqrt((a[i].x - s[k].x) * (a[i].x - s[k].x) + (a[i].y - s[k].y) * (a[i].y - s[k].y)) / sqrt((s[k].x - s[k - 1].x) * (s[k].x - s[k - 1].x) + (s[k].y - s[k - 1].y) * (s[k].y - s[k - 1].y));
			if (yy > xx)
			{
				xx = yy;
				l = i;
			}
		}
		if (color[l] == 1)
		{
			flag = 0;
		}
		else
		{
			s[++k] = a[l];
		}
	}
}

int main()
{
	int i;
	scanf("%d", &m);
	for (i = 1; i <= m; i++)
	{
		scanf("%lf%lf", &a[i].x, &a[i].y);
	}
	find_tubao();
	for (i = 1; i <= k; i++)
	{
		printf("%lf %lf\n", s[i].x, s[i].y);
	}
	return 0;
}

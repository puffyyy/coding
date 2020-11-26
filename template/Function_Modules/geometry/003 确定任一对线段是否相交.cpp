#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define maxm 1000005

struct word
{
	double x1;
	double y1;
	double x2;
	double y2;
	struct word *next;
	int seg;
};
typedef struct word Node;
typedef struct word *Nodeptr;

struct point
{
	double x;
	double y;
	int seg;
	int size;
};
typedef struct point Node2;
typedef struct point *Nodeptr2;

Node a[maxm];
Node2 b[maxm * 2];
Nodeptr list, p, q, r;
int m;

double max(double a, double b)
{
	if (a >= b)
	{
		return a;
	}
	else
	{
		return b;
	}
}

double min(double a, double b)
{
	if (a <= b)
	{
		return a;
	}
	else
	{
		return b;
	}
}

double direction(int i, int j, int k) //��������
{
	if (k == 1)
	{
		return (a[j].x1 - a[i].x1) * (a[i].y2 - a[i].y1) - (a[j].y1 - a[i].y1) * (a[i].x2 - a[i].x1);
	}
	else
	{
		return (a[j].x2 - a[i].x1) * (a[i].y2 - a[i].y1) - (a[j].y2 - a[i].y1) * (a[i].x2 - a[i].x1);
	}
}

int on_segment(int i, int j, int k) //�ж��߶�j������ĳһ�����Ƿ����߶�i��
{
	if (k == 1)
	{
		if (min(a[i].x1, a[i].x2) <= a[j].x1 && a[j].x1 <= max(a[i].x1, a[i].x2) && min(a[i].y1, a[i].y2) <= a[j].y1 && a[j].y1 <= max(a[i].y1, a[i].y2))
		{
			return 1;
		}
		else
		{
			return 0;
		}
	}
	else
	{
		if (min(a[i].x1, a[i].x2) <= a[j].x2 && a[j].x2 <= max(a[i].x1, a[i].x2) && min(a[i].y1, a[i].y2) <= a[j].y2 && a[j].y2 <= max(a[i].y1, a[i].y2))
		{
			return 1;
		}
		else
		{
			return 0;
		}
	}
}

int intersect(int i, int j) //�ж��߶�i���߶�j�Ƿ��ཻ
{
	double d1 = direction(j, i, 1);
	double d2 = direction(j, i, 2);
	double d3 = direction(i, j, 1);
	double d4 = direction(i, j, 2);
	if (((d1 > 0 && d2 < 0) || (d1 < 0 && d2 > 0)) && ((d3 > 0 && d4 < 0) || (d3 < 0 && d4 > 0)))
	{
		return 1;
	}
	else if (d1 > -0.00000000001 && d1 < 0.00000000001 && on_segment(j, i, 1))
	{
		return 1;
	}
	else if (d2 > -0.00000000001 && d2 < 0.00000000001 && on_segment(j, i, 2))
	{
		return 1;
	}
	else if (d3 > -0.00000000001 && d3 < 0.00000000001 && on_segment(i, j, 1))
	{
		return 1;
	}
	else if (d4 > -0.00000000001 && d4 < 0.00000000001 && on_segment(i, j, 2))
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

int cmp(const void *p1, const void *p2)
{
	Node2 xx1 = *(Nodeptr2)p1;
	Node2 xx2 = *(Nodeptr2)p2;
	if (xx1.x > xx2.x)
	{
		return 1;
	}
	else if (xx1.x < xx2.x)
	{
		return -1;
	}
	else if (xx1.size == 2 && xx2.size == 1)
	{
		return 1;
	}
	else if (xx1.size == 1 && xx2.size == 2)
	{
		return -1;
	}
	else if (xx1.y > xx2.y)
	{
		return 1;
	}
	else
	{
		return -1;
	}
}

int any_intersect()
{
	int i, j, k, l, flag;
	qsort(b + 1, 2 * m, sizeof(Node2), cmp);
	list = (Nodeptr)malloc(sizeof(Node));
	list->next = NULL;
	for (i = 1; i <= 2 * m; i++)
	{
		if (b[i].size == 1)
		{
			q = (Nodeptr)malloc(sizeof(Node));
			l = b[i].seg;
			q->x1 = a[l].x1;
			q->y1 = a[l].y1;
			q->x1 = a[l].x2;
			q->y1 = a[l].y2;
			q->seg = l;
			q->next = NULL;
			flag = 0;
			r = list;
			while (r->next != NULL && flag == 0)
			{
				p = r->next;
				double z = (p->x2 - p->x1) * p->y1 + (p->y2 - p->y1) * (b[i].x - p->x1) - b[i].y * (p->x2 - p->x1);
				if (z > -0.000000001 && z < 0.000000001 && b[i].x >= min(p->x1, p->x2) && b[i].x <= max(p->x1, p->x2))
				{
					return 1;
				}
				else if (z < 0 || (z > -0.000000001 && z < 0.000000001))
				{
					flag = 1;
				}
				if (flag == 0)
				{
					r = r->next;
				}
			}
			r->next = q;
			q->next = p;
		}
		else
		{
			l = b[i].seg;
			for (r = list; r->next->seg != l; r = r->next)
			{
			}
			p = r;
			q = r->next->next;
			if (p != list && q != NULL && intersect(p->seg, q->seg) == 1)
			{
				return 1;
			}
			else if (p != list && intersect(p->seg, l) == 1)
			{
				return 1;
			}
			else if (q != NULL && intersect(l, q->seg) == 1)
			{
				return 1;
			}
			else
			{
				p->next = q;
			}
		}
	}
	return 0;
}

int main()
{
	int i;
	scanf("%d", &m);
	for (i = 1; i <= m; i++)
	{
		scanf("%lf%lf%lf%lf", &a[i].x1, &a[i].y1, &a[i].x2, &a[i].y2); //a[i]Ϊ�߶�
		b[2 * i - 1].x = a[i].x1;									   //b[i]Ϊ��
		b[2 * i - 1].y = a[i].y1;
		b[2 * i - 1].seg = i;
		b[2 * i].x = a[i].x2;
		b[2 * i].y = a[i].y2;
		b[2 * i].seg = i;
		if (a[i].x1 < a[i].x2)
		{
			b[2 * i - 1].size = 1; //��˵�
			b[2 * i].size = 2;	   //�Ҷ˵�
		}
		else
		{
			b[2 * i - 1].size = 2;
			b[2 * i].size = 1;
		}
	}
	int z = any_intersect();
	printf("%d", z);
	return 0;
}

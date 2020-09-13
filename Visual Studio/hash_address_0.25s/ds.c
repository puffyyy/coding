
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define max(a, b) ((a) > (b) ? (a) : (b))
#define min(a, b) ((a) > (b) ? (b) : (a))
#define MAXLEN 100000
#define HashLen 1403641 //10000079//12582917
FILE *in_article1, *in_article2, *in_stop_words, *in_dictionary, *out_result;
struct words
{
	char str[46];
	int cnt[2];
	struct words *next;
} * dic[HashLen + 5];
int n;
inline char gc(FILE *in)
{
	static char buf[MAXLEN], *s, *t;
	return (s == t) && (t = (s = buf) + fread(buf, 1, MAXLEN, in)), s == t ? -1 : *s++;
}
int cmp0(const void *c, const void *d)
{
	struct words **a = (struct words **)c;
	struct words **b = (struct words **)d;
	if ((*a)->cnt[0] > (*b)->cnt[0])
		return -1;
	else if ((*a)->cnt[0] < (*b)->cnt[0])
		return 1;
	else
		return strcmp((*a)->str, (*b)->str);
}
int cmp1(const void *c, const void *d)
{
	struct words **a = (struct words **)c;
	struct words **b = (struct words **)d;
	if ((*a)->cnt[1] > (*b)->cnt[1])
		return -1;
	else if ((*a)->cnt[1] < (*b)->cnt[1])
		return 1;
	else
		return strcmp((*a)->str, (*b)->str);
}
inline int cmp_fre(struct words *a, struct words *b, int order)
{
	if (a->cnt[order] > b->cnt[order])
		return 1;
	else if (a->cnt[order] < b->cnt[order])
		return -1;
	else
		return (-1) * strcmp(a->str, b->str);
}
//**************************************************************
/*���ȶ��� ��*/
struct words **listA;
struct words **listB;
void AdjustDown(struct words **a, int s, int n, int order)
{
	a[0] = a[s];						//a[0]��ʱ���
	for (int i = 2 * s; i <= n; i *= 2) //����k�ϴ���ֽڵ�����ɸѡ
	{
		if (i < n && cmp_fre(a[i], a[i + 1], order) > 0)
			i++; //ȡK�ϴ���ӽڵ���±�
		if (cmp_fre(a[0], a[i], order) <= 0)
			break; //ɸѡ����
		else
		{
			a[s] = a[i]; //��a[i]������˫�׽ڵ���
			s = i;		 //�޸�kֵ���Ա��������ɸѡ
		}
	}
	a[s] = a[0]; //��ɸѡ�ڵ��ֵ��������λ��
}
void BuildMaxHeap(struct words **a, int n, int order)
{
	for (int i = n / 2; i > 0; i--)
		AdjustDown(a, i, n, order); //���µ���
}
void search(struct words **list, int order)
{
	int heapsize = n, i = 0;
	struct words init;
	*init.str = '\0';
	init.cnt[order] = -1;
	init.next = NULL;
	for (int j = 1; j <= heapsize; j++)
	{ //initialize
		list[j] = &init;
	}
	struct words *pointer = NULL;
	for (int i = 0; i < HashLen; i++)
	{
		while (dic[i] == NULL)
			i++;
		if (i > HashLen - 1)
			break;
		pointer = dic[i];
		while (pointer != NULL)
		{
			if (pointer->cnt[order] > list[1]->cnt[order] || (pointer->cnt[order] == list[1]->cnt[order] && strcmp(pointer->str, list[1]->str) < 0))
			{
				list[1] = pointer;
				AdjustDown(list, 1, n, order);
			}
			pointer = pointer->next;
		}
	}
}
/***************************************************************/
/*��ϣ�� */
//int crash = 0;
unsigned int bkdr_hash(char *key)
{
	char *str = key;
	unsigned int seed = 31;
	unsigned int hash = 0;
	for (; *str != '\0'; str++)
		hash = hash * seed + *str;
	return hash % HashLen;
}
//����dic ���� hash��
void createElement(char *s)
{
	unsigned int pos = bkdr_hash(s);
	struct words *pointer = *(dic + pos);
	if (pointer == NULL)
	{
		struct words *newitem = (struct words *)malloc(sizeof(struct words));
		strcpy(newitem->str, s);
		newitem->cnt[0] = 0;
		newitem->cnt[1] = 0;
		newitem->next = NULL;
		*(dic + pos) = newitem;
		return;
	}
	else
	{
		while (pointer->next != NULL)
		{
			pointer = pointer->next;
		}
		struct words *newitem;
		newitem = (struct words *)malloc(sizeof(struct words));
		strcpy(newitem->str, s);
		newitem->cnt[0] = 0;
		newitem->cnt[1] = 0;
		newitem->next = NULL;
		pointer->next = newitem;
		//crash++;
		return;
	}
}
void countElement(char *s, int order)
{
	unsigned int pos = bkdr_hash(s);
	struct words *pointer = *(dic + pos);
	while (pointer != NULL)
	{
		if (strcmp(s, pointer->str) == 0)
		{
			pointer->cnt[order]++;
			return;
		}
		pointer = pointer->next;
	}
}
void deleteElement(char *s)
{
	unsigned int pos = bkdr_hash(s);
	struct words *pointer = dic[pos], *prep = pointer;
	if (pointer != NULL && strcmp(s, pointer->str) == 0)
	{
		dic[pos] = pointer->next;
		return;
	}
	while (pointer != NULL)
	{
		if (strcmp(s, pointer->str) == 0)
		{
			prep->next = pointer->next; //free();
			return;
		}
		prep = pointer;
		pointer = pointer->next;
	}
}
/***************************************************************/
inline int xchar(FILE *in)
{
	static char buf[100000];
	static int len = 0, pos = 0;
	if (pos == len)
		pos = 0, len = fread(buf, 1, 100000, in);
	if (pos == len)
		return -1;
	return buf[pos++];
}
inline void xstring(char *s, FILE *in)
{
	int c = xchar(in);
	if (c == -1)
	{
		*s = -1;
		return;
	}
	while (c <= 65 || c >= 123)
		c = xchar(in);
	for (; c > 65 && c < 123; c = xchar(in))
		*s++ = c;
	*s = 0;
}
int read_string(char *s, FILE *in)
{

	char ch = gc(in);
	if (ch == EOF)
		return 0;
	for (; (ch == ' ' || ch == '\n' || ch == '\r' || ch == '\t'); ch = gc(in))
		;
	if (ch == EOF)
		return 0;
	for (; !(ch == ' ' || ch == '\n' || ch == '\r' || ch == '\t' || ch == EOF); ch = gc(in))
		*s++ = ch;
	*s = 0;
	return 1;
}
void delete_stopword()
{
	char badch[46];
	for (;;)
	{
		xstring(badch, in_stop_words);
		if (*badch == -1)
			break;
		deleteElement(badch);
	}
}
void read_article(FILE *in, int order)
{
	/*���Ҳ��������洢��dic[]*/
	int i = 0, pos = 0;
	char *s = (char *)malloc(sizeof(char) * 46), temp = '\0';
	*s = '\0';
	//while ((temp = fgetc(in)) != EOF) {
	while ((temp = gc(in)) != EOF)
	{
		if (96 < temp && 123 > temp)
		{
			*(s + (i++)) = temp;
		}
		else if (64 < temp && 91 > temp)
		{
			*(s + (i++)) = temp + 32;
		}
		else
		{
			if (*s != '\0')
			{
				*(s + i) = '\0';
				countElement(s, order);
			}
			i = 0;
			*s = '\0';
		}
	}
	free(s);
}

int main()
{
	/*file open*/
	in_dictionary = fopen("dictionary.txt", "r");
	in_stop_words = fopen("stopwords.txt", "r");
	in_article1 = fopen("article1.txt", "r");
	in_article2 = fopen("article2.txt", "r");
	out_result = fopen("results.txt", "w");
	if (in_dictionary == NULL || in_stop_words == NULL || in_article1 == NULL || in_article2 == NULL || out_result == NULL)
	{
		printf("can not read\n");
		return 0;
	}
	/*read dictionary*/
	int i = 1;
	char tmp[46];
	for (;;)
	{
		xstring(tmp, in_dictionary);
		if (*tmp == -1)
			break;
		createElement(tmp);
	}
	//printf("crash:%4d", crash);
	/*check dictionary*/
	delete_stopword();
	fclose(in_dictionary);
	fclose(in_stop_words);

	//***********************************************
	scanf("%d", &n);
	//n = 500;
	//***********************************************

	/*count frequence*/
	read_article(in_article1, 0);
	read_article(in_article2, 1);
	fclose(in_article1);
	fclose(in_article2);

	//heap�д洢dic�ĵ�ַ
	/*initialize*/
	listA = (struct words **)malloc(sizeof(struct words *) * (n + 2));
	listB = (struct words **)malloc(sizeof(struct words *) * (n + 2));

	//search_n(heap[0].list, &heap[0], 0);
	search(listA, 0);
	qsort(listA + 1, n, sizeof(struct words *), cmp0);

	//search_n(heap[1].list, &heap[1], 1);
	search(listB, 1);
	qsort(listB + 1, n, sizeof(struct words *), cmp1);

	int fr1 = 0, fr2 = 0, fra = 0, frb = 0;
	double ans, a, b;

	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= n; j++)
		{
			if (listA[i] == listB[j])
			{
				fra += listA[i]->cnt[0];
				frb += listB[j]->cnt[1];
			}
		}
		fr1 += listA[i]->cnt[0];
		fr2 += listB[i]->cnt[1];
	}
	a = (double)fra / (double)fr1;
	b = (double)frb / (double)fr2;
	ans = (min(a, b)) / (max(a, b));
	printf("%.5lf", ans);
	fprintf(out_result, "%.5lf\n", ans);
	fputc('\n', out_result);

	for (int i = 1; i <= n; i++)
	{
		char *s = listA[i]->str;
		while (*s)
			fputc(*s++, out_result);
		fprintf(out_result, " %d\n", listA[i]->cnt[0]);
	}
	fputc('\n', out_result);
	for (int i = 1; i <= n; i++)
	{

		char *s = listB[i]->str;
		while (*s)
			fputc(*s++, out_result);
		fprintf(out_result, " %d\n", listB[i]->cnt[1]);
	}
	fclose(out_result);
	return 0;
}
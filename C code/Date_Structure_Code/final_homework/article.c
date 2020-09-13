#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <time.h>
#define max(a,b) (a)>(b)?(a):(b)
#define min(a,b) (a)>(b)?(b):(a)
FILE* in_article1, * in_article2, * in_stop_words, * in_dictionary, * out_result;
struct words {
	char str[46];
	int cnt[2];
}dic[1000005];
int dic_lenth=-1, n, listsize;
int cmp0(const void* c, const void* d) {
	int* a = (int*)c;
	int* b = (int*)d;
	if (dic[*a].cnt[0] > dic[*b].cnt[0])return -1;
	else if (dic[*a].cnt[0] < dic[*b].cnt[0])return 1;
	else return  strcmp(dic[*a].str, dic[*b].str);
}
int cmp1(const void* c, const void* d) {
	int* a = (int*)c;
	int* b = (int*)d;
	if (dic[*a].cnt[1] > dic[*b].cnt[1])return -1;
	else if (dic[*a].cnt[1] < dic[*b].cnt[1])return 1;
	else return  strcmp(dic[*a].str, dic[*b].str);
}
inline int cmp_fre(struct words* a, struct words* b, int order) {
	if (a->cnt[order] > b->cnt[order])return 1;
	else if (a->cnt[order] < b->cnt[order])return -1;
	else return (-1) * strcmp(a->str, b->str);
}
int binarysearch(struct words *a, char* x, int lenth) {
	int left = 0, right = lenth - 1, mid,flag=2;
	while (left <= right) {
		mid = left + (right - left) / 2;
		flag = strcmp((a + mid)->str, x);
		if (flag == 0)return mid;
		if (flag <= 0) 
			left = mid + 1;
		else
			right = mid - 1;
	}

	return right;
}
void read_article(FILE* in, int order) {
	/*查找并计数，存储进dic[]*/
	int i = 0, pos = 0;
	char* s = (char*)malloc(sizeof(char) * 46), temp='\0';
	*s = '\0';

	while ((temp = fgetc(in)) != EOF) {
		if (96 < temp && 123 > temp) {
			*(s + (i++)) = temp;
		}
		else if (64 < temp && 91 > temp) {
			*(s + (i++)) = temp + 32;
		}
		else {
			if (*s!='\0') {
				*(s + i) = '\0';
				pos = binarysearch(dic, s, dic_lenth);
				if (strcmp(dic[pos].str, s) == 0) {
					dic[pos].cnt[order]++;
				}	
			}
			i = 0;
			*s = '\0';
		}
	}
	free(s);
}

void delete_stopword() {
	char badch[30];
	while (fscanf(in_stop_words, "%s", badch) != -1) {
		int pos=binarysearch(dic, badch, dic_lenth);
		if (strcmp(dic[pos].str, badch) == 0) {
			dic[pos].cnt[0] = -2147483647;
			dic[pos].cnt[1] = -2147483647;
		}
	}
}

//************************************************
/*优先队列 类*/
struct Heap {
	int maxsize;
	int* list;
}heap[2];

void AdjustDown(int* a, int s, int n, int order)
{
	a[0] = a[s];//a[0]暂时存放
	for (int i = 2 * s; i <= n; i *= 2)//沿着k较大的字节点向下筛选
	{
		if (i < n && cmp_fre(&dic[a[i]], &dic[a[i + 1]], order)>0)
			i++;//取K较大的子节点的下标
		if (cmp_fre(&dic[a[0]], &dic[a[i]], order) <= 0) break;//筛选结束
		else
		{
			a[s] = a[i];//将a[i]调整到双亲节点上
			s = i;//修改k值，以便继续向下筛选
		}
	}
	a[s] = a[0];//被筛选节点的值放在最终位置
}
void BuildMaxHeap(int* a, int n, int order)
{
	for (int i = n / 2; i > 0; i--)
		AdjustDown(a, i, n, order);//向下调整
}

void Heap_Sort(int* a, int n,int order)//n是指待排序列 的元素个数，数组a的长度是n+1，a[0]不使用
{
	BuildMaxHeap(a, n,order);//创建大根堆,时间复杂度是o(n)
	//调整大根堆，时间复杂度是o(nlgn)
	for (int i = n; i > 1; i--)
	{
		int temp = a[1];
		a[1] = a[i];
		a[i] = a[1];
		AdjustDown(a, 1, i - 1,order);//向下调整
	}
}
void search(int* list, struct Heap* heaphead, int order) {
	int heapsize = n > dic_lenth ? dic_lenth : n;
	for (int i = 1; i <= heapsize; i++) {// 1...dic_lenth
		heaphead->list[i] = i;
	}
	BuildMaxHeap(heaphead->list, n,order);
	for (int i = n; i < dic_lenth; i++)
	{
		if (cmp_fre(&dic[i] , &dic[list[1]],order)<0)
			continue;
		else
		{
			list[1] = i;
			AdjustDown(list, 1, n,order);
		}
	}
	if (cmp_fre(&dic[0] , &dic[list[1]],order)>0)
	{
		list[1] = 0;
		AdjustDown(list, 1, n,order);
	}
}
inline char nc1() {
	static char buf[100000], * p1 = buf, * p2 = buf;
	return p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 100000, in_dictionary), p1 == p2) ? EOF : *p1++;
}
int IOerror = 0;
inline char nc() {
	static char buf[100000], * p1 = buf + 100000, * pend = buf + 100000;
	if (p1 == pend) {
		IOerror = 0;
		p1 = buf; pend = buf + fread(buf, 1, 10, in_dictionary);
		if (pend == p1) { IOerror = 1; return -1; }
	}
	return *p1++;
}
inline void _read(char *s) {
	
	char ch = nc();
	for (; (ch == ' ' || ch == '\n' || ch == '\r' || ch == '\t'); ch = nc());
	if (IOerror)return;
	for (; !(ch == ' ' || ch == '\n' || ch == '\r' || ch == '\t') && !IOerror; ch = nc())*s++ = ch;
	*s = 0;
}
void read_quick() {
	
	//ch == ' ' || ch == '\n' || ch == '\r' || ch == '\t';
}
int main()
{
	/*file open*/
	in_dictionary = fopen("dictionary.txt", "r");
	in_stop_words = fopen("stopwords.txt", "r");
	in_article1 = fopen("article1.txt", "r");
	in_article2 = fopen("article2.txt", "r");
	out_result = fopen("results.txt", "w");
	if (in_dictionary == NULL || in_stop_words == NULL || in_article1 == NULL || in_article2 == NULL || out_result == NULL) {
		printf("can not read\n");
		return 0;
	}
	/*read dictionary*/
	for (;;) {
		//if (fscanf(in_dictionary, "%s", dic[++dic_lenth].str) == -1)break;
		_read(dic[++dic_lenth].str);
		if (*dic[dic_lenth].str == 0)break;
	}
	/*check dictionary*/
	delete_stopword();
	extern fclose(in_dictionary);
	extern fcloce(in_stop_words);
	scanf("%d", &n);
	//n = 500;
	/*count frequence*/
	read_article(in_article1, 0);
	read_article(in_article2, 1);
	extern fclose(in_article1);
	extern fcloce(in_article2);
	/*initialize*/
	heap[0].maxsize = n + 2;
	heap[0].list = (int*)malloc(sizeof(int) * (n + 2));
	heap[1].maxsize = n + 2;
	heap[1].list = (int*)malloc(sizeof(int) * (n + 2));
	
	//search_n(heap[0].list, &heap[0], 0);
	search(heap[0].list, &heap[0], 0);
	qsort(heap[0].list + 1, n, sizeof(int), cmp0);
	
	//search_n(heap[1].list, &heap[1], 1);
	search(heap[1].list, &heap[1], 1);
	qsort(heap[1].list + 1, n, sizeof(int), cmp1);
	
	int fr1 = 0, fr2 = 0, fra = 0,frb = 0 ;
	double ans,a,b;

	for (int i=1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			if (heap[0].list[i] == heap[1].list[j])
			{
				fra += dic[heap[0].list[i]].cnt[0];
				frb += dic[heap[1].list[j]].cnt[1];
			}
		}
		fr1 += dic[heap[0].list[i]].cnt[0];
		fr2 += dic[heap[1].list[i]].cnt[1];
	}
	a = (double)fra / (double)fr1;
	b = (double)frb / (double)fr2;
	ans = (min(a, b)) / (max(a, b));
	printf("%.5lf", ans);
	fprintf(out_result,"%.5lf\n",ans);
	fputc('\n', out_result);
	
	for (int i = 1; i <= n; i++)
		fprintf(out_result, "%s %d\n", dic[heap[0].list[i]].str, dic[heap[0].list[i]].cnt[0]);
	fputc('\n', out_result);
	for (int i = 1; i <= n; i++) {
		/*
		char* s = dic[heap[1].list[i]].str;
		while (*s)fputc(*s++,out_result);
		fprintf(out_result, " %d\n", , dic[heap[1].list[i]].cnt[1]);*/
		fprintf(out_result, "%s %d\n", dic[heap[1].list[i]].str, dic[heap[1].list[i]].cnt[1]);
	}
	//fflush(out_result);
	extern fcloce(out_result);
	return 0;
}
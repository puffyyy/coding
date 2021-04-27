//�ļ�ѹ��-Huffmanʵ��
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXSIZE 32

struct tnode
{ //Huffman���ṹ
	char c;
	int weight; //���ڵ�Ȩ�أ�Ҷ�ڵ�Ϊ�ַ������ĳ��ִ���
	struct tnode *left, *right;
};
int Ccount[128] = {0};			  //���ÿ���ַ��ĳ��ִ�������Ccount[i]��ʾASCIIֵΪi���ַ����ִ���
struct tnode *Root = NULL;		  //Huffman���ĸ��ڵ�
char HCode[128][MAXSIZE] = {{0}}; //�ַ���Huffman���룬��HCode['a']Ϊ�ַ�a��Huffman���루�ַ�����ʽ��
int Step = 0;					  //ʵ�鲽��
FILE *Src, *Obj;

void statCount();	//����1��ͳ���ļ����ַ�Ƶ��
void createHTree(); //����2������һ��Huffman�������ڵ�ΪRoot
void makeHCode();	//����3������Huffman������Huffman����
void atoHZIP();		//����4������Huffman���뽫ָ��ASCII���ı��ļ�ת����Huffman���ļ�

void print1();				  //�������?1�Ľ��?
void print2(struct tnode *p); //�������?2�Ľ��?
void print3();				  //�������?3�Ľ��?
void print4();				  //�������?4�Ľ��?

int main()
{
	if ((Src = fopen("input.txt", "r")) == NULL)
	{
		fprintf(stderr, "%s open failed!\n", "input.txt");
		return 1;
	}
	if ((Obj = fopen("output.txt", "w")) == NULL)
	{
		fprintf(stderr, "%s open failed!\n", "output.txt");
		return 1;
	}

	statCount(); //ʵ�鲽��1��ͳ���ļ����ַ����ִ�����Ƶ�ʣ�
	//print1();		 //���ʵ�鲽��?1���?
	createHTree(); //ʵ�鲽��2�������ַ�Ƶ��������Ӧ��Huffman��
	//print2(Root);	 //���ʵ�鲽��?2���?
	makeHCode(Root); //ʵ�鲽��3������RootΪ���ĸ���Huffman��������ӦHuffman����
	//print3();		 //���ʵ�鲽��?3���?
	atoHZIP();
	//print4(); //ʵ�鲽��4����Huffman��������ѹ���ļ��������ʵ�鲽��?4���?

	fclose(Src);
	fclose(Obj);

	return 0;
}

//��ʵ�鲽��1����ʼ

void statCount()
{
	char ch;
	while ((ch = fgetc(Src)) != EOF)
		Ccount[ch]++;
	Ccount[0] = 1;
}

//��ʵ�鲽��1������

//��ʵ�鲽��2����ʼ
int cmp(const void *a, const void *b)
{
	struct tnode **c = (struct tnode **)a;
	struct tnode **d = (struct tnode **)b;
	if ((*c)->weight == (*d)->weight)
		return (*c)->c - (*d)->c;
	else
		return (*c)->weight - (*d)->weight;
}
void createHTree()
{
	struct tnode *forest[256], *p;
	int i;
	int front = 0;
	int rear = 255;
	int count = 0;
	for (i = 0; i < 128; i++)
		if (Ccount[i] > 0)
		{
			p = (struct tnode *)malloc(sizeof(struct tnode));
			p->c = i;
			p->weight = Ccount[i];
			p->left = p->right = NULL;
			rear = (rear + 1) % 256;
			forest[rear] = p;
			++count;
		}
	qsort(forest, count, sizeof(struct tnode *), cmp);
	while (count > 1)
	{

		p = (struct tnode *)malloc(sizeof(struct tnode));
		p->left = forest[front];
		forest[front] = NULL;
		front = (front + 1) % 256;
		p->right = forest[front];
		forest[front] = NULL;
		front = (front + 1) % 256;
		p->weight = p->left->weight + p->right->weight;

		rear = (rear + 1) % 256;
		--count;
		for (i = front; i != (rear) % 256; i++)
		{
			if (forest[i]->weight > p->weight)
				break;
		}
		for (int j = rear; j >= i; j--)
		{

			forest[j + 1] = forest[j];
		}
		forest[i] = p;
	}

	Root = forest[front];
}

//��ʵ�鲽��2������

//��ʵ�鲽��3����ʼ

void visitHTree(struct tnode *tree, int len, char s[])
{
	if (tree == NULL)
		return;
	if (tree->left == NULL && tree->right == NULL)
	{
		s[len] = '\0';
		strcpy(HCode[tree->c], s);
		return;
	}
	s[len] = '0';
	visitHTree(tree->left, len + 1, s);
	s[len] = '1';
	visitHTree(tree->right, len + 1, s);
}
void makeHCode()
{
	char str[21];
	visitHTree(Root, 0, str);
	//print3();
}

//��ʵ�鲽��3������

//��ʵ�鲽��4����ʼ

void atoHZIP()
{
	unsigned char hc;
	int i = 0, bit = 0;
	char *s, ch;
	rewind(Src);
	while ((ch = fgetc(Src)) != EOF)
	{
		s = HCode[ch];
		for (i = 0; s[i] != '\0'; i++)
		{
			++bit;
			hc = (hc << 1) | (s[i] - '0');
			//printf("%c", s[i]);
			if ((bit) % 8 == 0)
			{
				fputc(hc, Obj); //�����Ŀ�꣨ѹ�����ļ���?
				printf("%x", hc);
				bit = 0;
				hc = '\0';
			}
		}
	}
	s = HCode[0];
	for (int i = 0; s[i] != 0; i++)
	{
		++bit;
		hc = (hc << 1) | (s[i] - '0');
		if ((bit) % 8 == 0)
		{
			fputc(hc, Obj); //�����Ŀ�꣨ѹ�����ļ���?
			printf("%x", hc);
			bit = 0;
			hc = '\0';
		}
	}
	if (bit != 8)
	{
		for (; bit != 8; bit++)
			hc = hc << 1;
		fputc(hc, Obj); //�����Ŀ�꣨ѹ�����ļ���?
		printf("%x", hc);
	}
	return;
}

//��ʵ�鲽��4������

void print1()
{
	int i;
	printf("NUL:1\n");
	for (i = 1; i < 128; i++)
		if (Ccount[i] > 0)
			printf("%c:%d\n", i, Ccount[i]);
}

void print2(struct tnode *p)
{
	if (p != NULL)
	{
		if ((p->left == NULL) && (p->right == NULL))
			switch (p->c)
			{
			case 0:
				printf("NUL ");
				break;
			case ' ':
				printf("SP ");
				break;
			case '\t':
				printf("TAB ");
				break;
			case '\n':
				printf("CR ");
				break;
			default:
				printf("%c ", p->c);
				break;
			}
		print2(p->left);
		print2(p->right);
	}
}

void print3()
{
	int i;

	for (i = 0; i < 128; i++)
	{
		if (HCode[i][0] != 0)
		{
			switch (i)
			{
			case 0:
				printf("NUL:");
				break;
			case ' ':
				printf("SP:");
				break;
			case '\t':
				printf("TAB:");
				break;
			case '\n':
				printf("CR:");
				break;
			default:
				printf("%c:", i);
				break;
			}
			printf("%s\n", HCode[i]);
		}
	}
}

void print4()
{
	long int in_size, out_size;

	fseek(Src, 0, SEEK_END);
	fseek(Obj, 0, SEEK_END);
	in_size = ftell(Src);
	out_size = ftell(Obj);

	printf("\nԭ�ļ���С��%ldB\n", in_size);
	printf("ѹ�����ļ���С��%ldB\n", out_size);
	printf("ѹ���ʣ�%.2f%%\n", (float)(in_size - out_size) * 100 / in_size);
}

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void gauss(double[], double[], double[], int);

int main(int argc, char *argv[])
{
	int n = 4;
	//	double a[4 * 4] = { 1, 1, 0, 3,
	//	                    2, 1, -1, 1,
	//	                    3, -1, -1, 3,
	//	                    -1, 2, 3, -1
	//	                  };
	//	double b[4]     = { 4, 1, -3, 4 };
	double a[4 * 4] = {1, 1, 0, 1,
					   1, 1, 1, 0,
					   0, 1, 1, 1,
					   1, 0, 1, 1};
	double b[4] = {20, 15, 17, 14};
	double x[4] = {};

	printf("增广矩阵\n");
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			printf("%f\t", a[i * n + j]);
		}
		printf("%f\n", b[i]);
	}
	printf("解向量\n");
	gauss(a, b, x, n);
	for (int i = 0; i < n; i++)
		printf("%f\t", x[i]);
	printf("\n");
	return 0;
}

void gauss(double a[], double b[], double x[], int n)
{ //列主元高斯消去法，a[]系数矩阵，b[]结果向量，x[]解向量，n阶数
	int i, j, k, exchangeline, exchangeflag = 0;
	double temp, max;

	for (k = 0; k < n - 1; k++)
	{ //k迭代次数
		max = a[k * n + k];
		for (i = k + 1; i < n; i++)
		{ //寻找主元，i行号
			if (fabs(max) < fabs(a[n * i + k]))
			{
				max = a[n * i + k];
				exchangeflag = 1;	  //交换标志
				exchangeline = n * i; //记录需要交换的行号
			}
		}
		if (exchangeflag)
		{ //换行，j列号
			for (j = 0; j < n; j++)
			{
				temp = a[exchangeline + j]; //对系数矩阵操作
				a[exchangeline + j] = a[k * n + j];
				a[k * n + j] = temp;
			}
			temp = b[exchangeline / n]; //对结果向量操作
			b[exchangeline / n] = b[k];
			b[k] = temp;
			exchangeflag = 0; //清除交换标志
		}
		for (i = k + 1; i < n; i++)
		{ //消元
			temp = a[i * n + k] / a[k * n + k];
			b[i] = b[i] - b[k] * temp; //对结果向量操作
			for (j = k; j < n; j++)
				a[i * n + j] = a[i * n + j] - a[k * n + j] * temp; //对系数矩阵操作
		}
	}
	for (i = n - 1; i > -1; i--)
	{ //回代
		temp = b[i];
		for (j = n - 1; j > i; j--)
			temp = temp - a[n * i + j] * x[j];
		x[i] = temp / a[i * n + i];
	}
}
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <math.h>
int x = 1;
int a[10000];
void sig_int(int signo)
{
	printf("%d", x);
}
int main()
{
	int x = 3;
	int c = 2;

	while (x--)
	{
		c = ~c;
		printf("%d\n", c);
	}

	return 0;
}
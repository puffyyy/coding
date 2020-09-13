#include<bits/stdc++.h>
using namespace std;
int k, res = 0;
 
bool check(int m)
{
	res = 0;
	for(int i = 1; i <= k; i++)
	{
		res = (res + m - 1) % (k * 2 - i + 1);  //res 为死亡位置， k*2-i+1为总人数
		if(res < k) return false;
	}
	return true;
}
 
int main()
{
	scanf("%d", &k);
	for(int i = k+1; ; i++)
	{
		if(check(i))
		{
			printf("%d\n", i);
			return 0;
		}
	}
} 
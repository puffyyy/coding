#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <cstdlib>
#include <algorithm>
using namespace std;
typedef long long ll;
const int inf =0x7fffffff;
int main() {
	int n,m,s,k;
	scanf("%d%d%d",&s,&n,&m);
	s-=n*m;
	printf("%d",(int)pow(n,s));
	return 0;
}

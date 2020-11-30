#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
ll n, a[100], sum, s[100], anss;
int main()
{
	scanf("%lld", &n);
	for (int i = 1; i <= n; i++)
	{
		scanf("%lld", &a[i]);
		sum += a[i];
	}
	sum /= n;
	for (int i = 1; i <= n; i++)
	{
		a[i] -= sum;
		s[i] = s[i - 1] + a[i];
	}
	sort(s + 1, s + n + 1);
	for (int i = 1; i <= n; i++)
	{
		anss += abs(s[n / 2 + 1] - s[i]);
	}
	printf("%lld", anss);
	return 0;
}
#include <iostream>
using namespace std;

int main()
{
	int n;
	cin >> n;
	while (n--)
	{
		long long a, b;
		cin >> a >> b;
		if ((a + 9223372036854775808 == 0) && (b + 9223372036854775808) == 0)
		{
			cout << "-18446744073709551616" << endl;
			continue;
		}
		if (a > 0 && b > 0)
		{
			unsigned long long ans = (unsigned long long)a + (unsigned long long)b;
			cout << ans << endl;
			continue;
		}
		else if (a < 0 && b < 0)
		{
			unsigned long long ans = (unsigned long long)(-a) + (unsigned long long)(-b);
			cout << '-' << ans << endl;
			continue;
		}
		else
		{
			long long ans = a + b;
			cout << ans << endl;
			continue;
		}
	}
	return 0;
}
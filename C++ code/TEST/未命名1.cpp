#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
ll t,mod,a,b,c,d,e;
ll f(ll x) {
	ll x1,x2,x3,x4;
	x1=x;
	x2=x1*x;
	x3=x2*x;
	x4=x3*x;
	ll res=(a*x4%mod+b*x3%mod+c*x2%mod+d*x1%mod+e%mod)%mod;
	while(res<0)
		res+=mod;
	return res;
}
int main() {
	scanf("%lld",&t);
	while(t--) {
		ll p1=0,p2=0,ans=1;
		scanf("%lld%lld%lld%lld%lld%lld",&mod,&a,&b,&c,&d,&e);
		p1=f(p1);
		p2=f(p2);
		p2=f(p2);
		while(p1!=p2) {
			p1=f(p1);
			p2=f(p2);
			p2=f(p2);
		}
		p1=f(p1);
		while(p1!=p2) {
			p1=f(p1);
			ans++;
		}
		printf("%lld\n",ans);
	}
	return 0;
}


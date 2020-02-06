#include<bits/stdc++.h>
#define LL long long
#define N 1111
using namespace std;
LL p[N],q[N],a[N],g[N],h[N];
pair<LL,LL> pell(LL n){
	p[1]=p[0]=h[1]=1;p[0]=q[1]=g[1]=0;a[2]=(LL)(floor(sqrt(n)+1e-8));
	for(int i=2;;i++){
		g[i]=-g[i-1]+a[i]*h[i-1];
		h[i]=(n-g[i]*g[i])/h[i-1];
		a[i+1]=(g[i]+a[2])/h[i];
		p[i]=a[i]*p[i-1]+p[i-2];
		q[i]=a[i]*p[i-1]+q[i-2];
		if(p[i]*p[i]-n*q[i]*q[i]==1)return make_pair(p[i],q[i]);
	}
}
int main(){
	LL n;
	scanf("%lld",&n);
	pair<LL,LL>an=pell(n);
	printf("%lld %lld\n",an.first,an.second);
}

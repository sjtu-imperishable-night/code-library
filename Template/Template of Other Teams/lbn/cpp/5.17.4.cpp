#include<bits/stdc++.h>
#define LL long long
using namespace std;
LL cal(LL m,LL d,LL l,LL r){
	if(l==0)return 0;
	if(d==0)return -1;
	if(d*2>m)return cal(m,m-d,m-r,m-l);
	if((l-1)/d<r/d)return (l-1)/d+1;
	LL k=cal(d,(-m%d+d)%d,l%d,r%d);
	return k==-1?-1:(k*m+l-1)/d+1;
}
int main(){
	LL d,l,r,m;
	scanf("%lld%lld%lld%lld",&d,&l,&r,&m);
	printf("%lld\n",cal(m,d,l,r));
}

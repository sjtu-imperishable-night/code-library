#include<bits/stdc++.h>
typedef long long LL; 
using namespace std;
LL Pw(LL a,LL b,LL p){
	LL v=1;
	for(;b;b>>=1,a=a*a%p)if(b&1)v=v*a%p;
	return v;
}
void multiply(LL&c,LL&d,LL a,LL b,LL w,LL p){
	LL cc=(a*c+b*d%p*w)%p,dd=(a*d+b*c)%p;
	c=cc;d=dd;
}
bool solve(LL n,LL p,LL&x){//求x^2 mod p=n的解
	if(p==2)return x=1,1;
	if(Pw(n,p/2,p)==p-1)return 0;//无解的情况
	LL c=1,d=0,b=1,a,w;
	do{
		a=rand()%p;
		w=(a*a-n+p)%p;
		if(w==0)return x=a,1;
	}while(Pw(w,p/2,p)!=p-1);
	for(LL d=(p+1)/2;d;d>>=1){
		if(d&1)multiply(c,d,a,b,w,p);
		multiply(a,b,a,b,w,p);
	}
	return x=c,1;
}
int main(){
	int T;LL n,p,a,b;
	scanf("%d",&T);
	for(;T--;){
		scanf("%lld%lld",&n,&p);n%=p;
		if(solve(n,p,a)){//有解，输出一个或两个解
			b=p-a;
			if(a>b)swap(a,b);
			if(a==b)printf("%lld\n",a);else printf("%lld %lld\n",a,b);
		}else puts("No root");//无解
	}
}

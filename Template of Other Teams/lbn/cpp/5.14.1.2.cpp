#include<bits/stdc++.h>
#define N 2222
#define W 2222222
#define M 1000000007
typedef long long LL;
int n,i,j;LL ans,v,x,X[N],Y[N],I[W];
LL inv(LL x){return x>=0?I[x]:M-I[-x];}
LL lagrange(int n,LL x,LL X[],LL Y[]){
	int i,j;LL ans=0,v;
	for(i=1;i<=n;i++){
		for(j=1;j<=n;j++)if(i!=j)v=v*(x-X[j])%M*inv(X[i]-X[j])%M;
		ans=(ans+v*Y[i])%M;
	}
	return (ans%M+M)%M;
}
int main(){
	for(I[1]=1,i=2;i<W;i++)I[i]=I[M%i]*(M-M/i)%M;
	scanf("%d",&n);
	for(i=1;i<=n;i++)scanf("%lld%lld",&X[i],&Y[i]);
	scanf("%lld",&x);
	printf("%lld",lagrange(n,x,X,Y));
}

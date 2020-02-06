#include<bits/stdc++.h>
#define LL long long
#define M 1000000007
#define N 205
using namespace std;
LL GXX(LL n,int m,LL a[],LL c[]){//求第n项,a[]中记录0~m-1项,c[]记录转移式
	LL v[N]={1},u[N*2],W=!!n,x,an=0;//f(n)=f(n-1)c(m-1)+f(n-2)c(m-2)+...+f(n-m)c(0)
	int i,j,t,b;
	for(x=n;x>1;x>>=1)W<<=1;
	for(x=0;W;W>>=1,x<<=1){
		memset(u,0,sizeof u);if(b=!!(n&W))x|=1;
		if(x<m)u[x]=1;else{
			for(i=0;i<m;i++)for(j=0,t=i+b;j<m;j++,t++)(u[t]+=v[i]*v[j])%=M;
			for(i=m*2-1;i>=m;i--)for(j=0,t=i-m;j<m;j++,t++)(u[t]+=c[j]*u[i])%=M;
		}
		copy(u,u+m,v);
	}
	for(i=0;i<m;i++)(an+=v[i]*a[i])%=M;
	return an;
}
int main(){
	LL n,f[N],g[N];int m,i;
	scanf("%lld%d",&n,&m);
	for(i=0;i<m;i++)scanf("%lld",&f[i]);
	for(i=0;i<m;i++)scanf("%lld",&g[i]);
	printf("%lld\n",GXX(n,m,f,g));
}

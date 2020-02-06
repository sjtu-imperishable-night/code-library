#include<bits/stdc++.h>
#define N 262144
#define M 998244353//模数
#define LL long long
using namespace std;
int G,g[N],A[N],B[N];int t,q[66];
LL Pw(LL a,LL b,LL p){LL V=1;for(a%=p;b;a=a*a%p,b>>=1)if(b&1)V=V*a%p;return V;}
void NTT(int *a,int n,int f=1){
	int i,j,k,m,u,v,w,wm;
	for(i=n>>1,j=1,k;j<n-1;j++){
		if(i>j)swap(a[i],a[j]);
		for(k=n>>1;k<=i;k>>=1)i^=k;i^=k;
	}
	for(m=2;m<=n;m<<=1)
		for(i=0,wm=Pw(G,f==1?(M-1)/m:(M-1)/m*(m-1),M);i<n;i+=m)
			for(j=i,w=1;j<i+(m>>1);j++){
				u=a[j],v=1ll*w*a[j+(m>>1)]%M;
				if((a[j]=u+v)>=M)a[j]-=M;
				if((a[j+(m>>1)]=u-v)<0)a[j+(m>>1)]+=M;
				w=1ll*w*wm%M;
			}
	if(f==-1)for(w=Pw(n,M-2,M),i=0;i<n;i++)a[i]=1ll*a[i]*w%M;
}
bool ok(LL g,LL p){//验证g是否是模p的原根
	for(int i=1;i<=t;i++)//如果g^((p-1)/qi) mod p=1，那么g不是模p的原根
		if(Pw(g,(p-1)/q[i],p)==1)return 0;
	return 1;
}
LL primitive_root(LL p){//求原根
	LL i,n=p-1,g=1;t=0;
	for(i=2;i*i<=n;i++)//分解质因数
        if(n%i==0)for(q[++t]=i;n%i==0;n/=i);
	if(n!=1)q[++t]=n;
	for(;;g++)//暴力枚举判断
		if(ok(g,p))return g;
}
int main(){
	int n,m,i;
	G=primitive_root(M);//求原根
	scanf("%d%d",&n,&m);
	for(i=0;i<=n;i++)scanf("%d",&A[i]);
	for(i=0;i<=m;i++)scanf("%d",&B[i]);
	NTT(A,N);NTT(B,N);
	for(i=0;i<N;i++)A[i]=1ll*A[i]*B[i]%M;
	for(NTT(A,N,-1),i=0;i<=n+m;i++)printf("%d ",A[i]);
}

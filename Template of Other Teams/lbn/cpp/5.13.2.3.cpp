#include<bits/stdc++.h>
#define N 262144//开两倍
#define M 1000000007
#define pi acos(-1)
#define LL long long
#define fr(i,n) for(int i=0;i<n;i++)
using namespace std;
typedef complex<double>CP;
void FFT(CP*a,int n){//变换
	int i,j,k,o;static CP w[N];
	for(i=n>>1,j=1,k;j<n-1;j++){
		if(i>j)swap(a[i],a[j]);
		for(k=n>>1;k<=i;k>>=1)i^=k;i^=k;
	}
	fr(i,n)w[i]=CP(cos(2*pi*i/n),sin(2*pi*i/n));
	for(i=2,o=n>>1;i<=n;i<<=1,o>>=1)
		for(j=0;j<n;j+=i){
			CP *l=a+j,*r=a+j+(i>>1),*p=w;
			for(k=0;k<i>>1;k++){
				CP tmp=*r * *p;
				*r=*l-tmp;*l=*l+tmp;
				l++;r++;p+=o;
			}
		}
}
void mul(int*x,int*y,int*z,int n){//求x*y，存到z中
	static CP a[N],b[N],A[N],B[N],C[N],D[N];
	fr(i,n){
		(x[i]+=M)%=M,(y[i]+=M)%=M;
		a[i]=CP(x[i]&32767,x[i]>>15);
		b[i]=CP(y[i]&32767,y[i]>>15);
	}
	FFT(a,n);FFT(b,n);
	fr(i,n){
		int j=(n-i)&(n-1);
		static CP da,db,dc,dd;
		da=(a[i]+conj(a[j]))*CP(0.5,0);db=(a[i]-conj(a[j]))*CP(0,-0.5);
		dc=(b[i]+conj(b[j]))*CP(0.5,0);dd=(b[i]-conj(b[j]))*CP(0,-0.5);
		A[j]=da*dc;B[j]=da*dd;C[j]=db*dc;D[j]=db*dd;
	}
	fr(i,n)a[i]=A[i]+B[i]*CP(0,1),b[i]=C[i]+D[i]*CP(0,1);
	FFT(a,n);FFT(b,n);
	fr(i,n){
		int da=(LL)(a[i].real()/n+0.5)%M,db=(LL)(a[i].imag()/n+0.5)%M,
			dc=(LL)(b[i].real()/n+0.5)%M,dd=(LL)(b[i].imag()/n+0.5)%M;
		z[i]=(da+((LL)(db+dc)<<15)+((LL)dd<<30))%M;
	}
}
int main(){
	int n,m,i,l=0,nn;
	static int a[N],b[N],c[N];
	scanf("%d%d",&n,&m);//输入
	fr(i,n+1)scanf("%d",&a[i]);
	fr(i,m+1)scanf("%d",&b[i]);
	for(l=0;(1<<l)<n+m+1;l++);//得到位数
	nn=1<<l;mul(a,b,c,nn);
	for(i=0;i<=n+m;i++)(c[i]+=M)%=M,printf("%d ",c[i]);
}

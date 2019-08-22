#include<bits/stdc++.h>
#define N 262144//多项式最高次数不能超过N
#define pi acos(-1)//π
using namespace std;
typedef complex<double>C;//复数类，支持复数运算
int n,m,i,t,g[N];C a[N],b[N];
void FFT(C *a,int f){//f=1为傅里叶变换，f=-1为逆傅里叶变换
	int i,j,k,p;
	for(i=0;i<N;i++)if(g[i]>i)swap(a[i],a[g[i]]);//蝴蝶变换，即迭代预处理
	for(i=1;i<N;i<<=1){//有lgN层，从下往上进行
		C e(cos(pi/i),f*sin(pi/i));//n次主单位根
		for(j=0;j<N;j+=i<<1){//每i*2个为一组计算
			C w(1,0);
			for(k=0;k<i;k++){//同时计算a[j+k]和a[j+k+i]
				C x=a[j+k],y=w*a[j+k+i];
				a[j+k]=x+y; //y_k=y_k0 +ω_n^k y_k1 
				a[j+k+i]=x-y; //y_(k+n/2)=y_k0-ω_n^k y_k1
				w*=e;//递推求得单位根
			}
		}
	}
	if(f<0)for(i=0;i<N;i++)a[i].real()/=N;//逆变换时最后要除N
}
int main(){
	scanf("%d%d",&n,&m);//读入两个多项式
	for(i=0;i<=n;i++)scanf("%lf",&a[i]);
	for(i=0;i<=m;i++)scanf("%lf",&b[i]);
	for(i=1;i<N;i++)g[i]=g[i>>1]>>1|((i&1)<<17);//蝴蝶变换递推预处理
	FFT(a,1),FFT(b,1);//DFT
	for(i=0;i<N;i++)a[i]=a[i]*b[i];//点值乘法
	FFT(a,-1);//IDFT
	for(i=0;i<=n+m;i++)printf("%d ",(int)(a[i].real()+0.5));//取整输出
}

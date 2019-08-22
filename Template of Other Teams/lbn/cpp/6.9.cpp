#include<bits/stdc++.h>// NOI2005月下柠檬树
#define sqr(x)((x)*(x))
using namespace std;typedef double D;
int n,i;D A,w,h,l,r,m,fl,fm,fr,fx[555],fy[555],gx[555],gy[555],a[555],R[555];
D F(D x){//得到f(x)的值
	D S=0;for(int i=1;i<=n;i++){
		if(fabs(x-a[i])<R[i])S=max(S,sqrt(sqr(R[i])-sqr(a[i]-x)));
		if(a[i+1]-a[i]>fabs(R[i+1]-R[i])&&fx[i]<x&&x<gx[i])
			S=max(S,(gy[i]-fy[i])/(gx[i]-fx[i])*(x-fx[i])+fy[i]);
	}return S;
}
D G(D a,D b,D fa,D fb,D fm){return(b-a)/6*(fa+4*fm+fb);}//辛普森积分
D C(D l,D fl,D m,D fm,D r,D fr,D z){//如果精度达到要求退出，否则递归
	D lm=(l+m)/2,rm=(m+r)/2,lz=F(lm),rz=F(rm),ls=G(l,m,fl,fm,lz),rs=G(m,r,fm,fr,rz);
	return fabs(ls+rs-z)<1e-6?z:C(l,fl,lm,lz,m,fm,ls)+C(m,fm,rm,rz,r,fr,rs);
}
int main(){
	for(scanf("%d%lf",&n,&w),w=1/tan(w),i=1;i<n+2;i++)scanf("%lf",&A),h+=A,a[i]=h*w;
	for(l=r=a[n+1],i=1;i<=n;i++)scanf("%lf",&R[i]),l=min(l,a[i]-R[i]),r=max(r,a[i]+R[i]);
	for(i=1;i<=n;i++)
		A=(R[i]-R[i+1])/(a[i+1]-a[i]),
		fx[i]=a[i]+R[i]*A,fy[i]=sqrt(sqr(R[i])-sqr(fx[i]-a[i])),
		gx[i]=a[i+1]+R[i+1]*A,gy[i]=sqrt(sqr(R[i+1])-sqr(gx[i]-a[i+1]));//两圆公切线
	m=(l+r)/2,fm=F(m),fl=F(l),fr=F(r);printf("%.2lf",2*C(l,fl,m,fm,r,fr,G(l,r,fl,fr,fm)));
}

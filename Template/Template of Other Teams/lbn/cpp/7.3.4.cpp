#include<bits/stdc++.h>//带权费马点
#define N 11111
using namespace std;
int n,i;
double anx,any,vx,vy,dis,nx,ny,T,nv,x[N],y[N],w[N];
double Rand(){return (double)(rand()%20000)/20000.0;}
double dist(double xx,double yy){
	nv=0;
	for(int i=1;i<=n;i++)nv+=sqrt((xx-x[i])*(xx-x[i])+(yy-y[i])*(yy-y[i]))*w[i];
	if(nv<dis)dis=nv,anx=xx,any=yy;
	return nv;
}
int main(){
	scanf("%d",&n);
	for(i=1;i<=n;i++)scanf("%lf%lf%lf",&x[i],&y[i],&w[i]),anx+=x[i],any+=y[i];
	anx/=(double)n;any/=(double)n;T=100000;//变化幅度
	vx=anx=vy=any;//(vx,vy)当前位置，(anx,any)最优解位置
	dis=dist(anx,any);//当前最优解
	for(;T>0.001;){//小于给定系数就退出
		nx=vx;ny=vy;
		nx=nx+T*(Rand()*2-1);
		ny=ny+T*(Rand()*2-1);//在当前位置的变化幅度内随机取一点
		nv=dist(vx,vy)-dist(nx,ny);//计算当前解
		if(nv>0||exp(nv/T)>rand())//如果当前解比最优解好那么取为当前解，否则以exp|当前解-最优解|/T的概率接受当前解
			vx=nx,vy=ny;
		T*=0.98;//降低搜索范围（降温）
	}
	printf("%.3lf %.3lf",anx,any);
}

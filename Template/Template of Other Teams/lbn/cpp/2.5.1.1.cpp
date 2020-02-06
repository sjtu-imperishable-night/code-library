#include<bits/stdc++.h>
#define N 300100
#define inf 2000000005
using namespace std;
int rt,id,sz[N],Cnt[N],F[N],V[N],c[N][2];
void ps(int k){
	sz[k]=sz[c[k][0]]+sz[c[k][1]]+Cnt[k];
}
void R(int x){
	int y=F[x],k=(c[y][0]==x);
	c[y][!k]=c[x][k];F[c[x][k]]=y;
	F[x]=F[y];if(F[y])c[F[y]][c[F[y]][1]==y]=x;
	c[x][k]=y;F[y]=x;ps(y);
}
void sy(int x,int g){
	int y;
	for(;(y=F[x])!=g;R(x))
		if(F[y]!=g)R((c[y][0]==x)==(c[F[y]][0]==y)?y:x);
	ps(x);if(!g)rt=x;
}
int fd(int z){//查找值z的标号，没有返回0 
	int x=rt,y;
	for(;V[x]!=z&&x;)y=x,x=c[x][z>V[x]];
	if(x)sy(x,0);else sy(y,0);
	return x;
}
void ins(int z){//加入一个权值为z的点 
	int x=rt,y=0;
	for(;V[x]!=z&&x;)sz[x]++,y=x,x=c[x][z>V[x]];
	if(x)Cnt[x]++;else{
		x=++id;sz[x]=Cnt[x]=1;
		V[x]=z;F[x]=y;
		if(y)c[y][z>V[y]]=x;
	}
	sy(x,0);
}
int kth(int x,int k){//找第k大
	if(!x)return 0;
	if(sz[c[x][0]]+1<=k&&k<=sz[c[x][0]]+Cnt[x])return sy(x,0),x;
	return k<=sz[c[x][0]]?kth(c[x][0],k):kth(c[x][1],k-sz[c[x][0]]-Cnt[x]);
}
int rank(int x){//求排名 
	return sy(x,0),sz[c[x][0]]+1;
}
int rankv(int z){
	int x=fd(z);
	return rank(x);
}
int pre(int x){//求节点x的前驱 
	sy(x,0);int y=c[rt][0];
	for(;c[y][1];y=c[y][1]);
	return sy(y,0),y;
}
int suc(int x){//求节点x的后继 
	sy(x,0);int y=c[rt][1];
	for(;c[y][0];y=c[y][0]);
	return sy(y,0),y;
}
void del(int x){//假设已经找到了要删除的点x 
	int p=pre(x),s=suc(x),y;
	sy(p,0);sy(s,rt);
	y=c[s][0];
	if(!--Cnt[y])c[s][0]=F[y]=0;
	ps(y);ps(s);ps(p);
}
int delv(int z){//删除值为x的一个元素 
	int x=fd(z);
	if(x)del(x);
}
int prev(int x){//返回值x的前驱的值 
	int y=fd(x),ff=0,an;
	if(!y)ins(x),y=fd(x),ff=1;
	an=V[pre(y)];
	if(ff)del(y);
	return an;
}
int sucv(int x){//返回值x的后继的值 
	int y=fd(x),ff=0,an;
	if(!y)ins(x),y=fd(x),ff=1;
	an=V[suc(y)];
	if(ff)del(y);
	return an;
}
int main(){
	int T,lx,x;
	V[1]=-inf;V[2]=inf;sz[1]=2;sz[2]=1;id=2;
	rt=1;c[1][1]=2;F[2]=1;Cnt[1]=Cnt[2]=1;
	scanf("%d",&T);
	for(;T--;){
		scanf("%d%d",&lx,&x);
		if(lx==1)ins(x);
		if(lx==2)delv(x);
		if(lx==3)printf("%d\n",rankv(x)-1);
		if(lx==4)printf("%d\n",V[kth(rt,x+1)]);
		if(lx==5)printf("%d\n",prev(x));
		if(lx==6)printf("%d\n",sucv(x));
	}
}

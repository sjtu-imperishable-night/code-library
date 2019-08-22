#include<bits/stdc++.h>
#define N 150005
#define M 300005
#define CL(a) memset(a,0,sizeof a)
using namespace std;
int F[N],FF[N];
namespace Left_Tree{//可持久化左偏树
	struct P{int l,r,h,v,x,y;}Tr[N*40];
	int RT[N],num;
	int New(P o){Tr[++num]=o;return num;}
	void start(){num=0;Tr[0].l=Tr[0].r=Tr[0].h=0;Tr[0].v=1e9;}
	int mg(int x,int y){
		if(!x)return y;
		if(Tr[x].v>Tr[y].v)swap(x,y);
		int o=New(Tr[x]);
		Tr[o].r=mg(Tr[o].r,y);
		if(Tr[Tr[o].l].h<Tr[Tr[o].r].h)swap(Tr[o].l,Tr[o].r);
		Tr[o].h=Tr[Tr[o].r].h+1;
		return o;	
	}
	void add(int&k,int v,int x,int y){
		int o=New(Tr[0]);
		Tr[o].v=v;Tr[o].x=x;Tr[o].y=y;
		k=mg(k,o);	
	}
}
using namespace Left_Tree;
struct SPFA{//SPFA，和原来的略有不同
	int h,t,tot,q[N],fir[N],la[M],ne[M],va[M],d[N];bool v[N];
	void in(){tot=0;CL(fir);}
	void ins(int x,int y,int z){la[++tot]=y;ne[tot]=fir[x];fir[x]=tot;va[tot]=z;}
	void work(int S,int n){
		int i,x,y;
		for(int i=1;i<=n;i++)d[i]=1e9,v[i]=0;
		for(h=d[q[t=1]=S]=0;h^t;)
			for(i=fir[x=q[h=h%n+1]],v[x]=0;i;i=ne[i])
				if(d[x]+va[i]<d[y=la[i]])if(d[y]=d[x]+va[i],F[y]=x,FF[y]=i,!v[y])v[q[t=t%n+1]=y]=1;
	}
}A;
struct Kshort{
	int tot,n,m,S,T,k,fir[N],va[M],la[M],ne[M];bool v[N];
	struct P{
		int x,y,z;P(){}
		P(int x,int y,int z):x(x),y(y),z(z){}
		bool operator<(P a)const{return a.z<z;}
	};
	priority_queue<P>Q;
	void in(){tot=0;CL(fir);}
	void ins(int x,int y,int z){la[++tot]=y;ne[tot]=fir[x];fir[x]=tot;va[tot]=z;}
	void init(){
		int i,x,y,z;
		in();A.in();start();
		scanf("%d%d",&n,&m);
		for(i=1;i<=m;i++)scanf("%d%d%d",&x,&y,&z),A.ins(y,x,z),ins(x,y,z);
		scanf("%d%d%d",&S,&T,&k);
		if(S==T)k++;//起点等于终点的特殊情况
		A.work(T,n);
	}
	void dfs(int x){
		if(v[x])return;v[x]=1;
		if(F[x])RT[x]=RT[F[x]];
		for(int i=fir[x],y;i;i=ne[i])
			if(y=la[i],A.d[y]!=1e9&&FF[x]!=i)add(RT[x],A.d[y]-A.d[x]+va[i],x,y);
		for(int i=A.fir[x];i;i=A.ne[i])if(F[A.la[i]]==x)dfs(A.la[i]);
	}
	int work(){
		int i,x;
		dfs(T);
		if(!--k)return A.d[S]==1e9?-1:A.d[S]; 
		P u,w;
		if(RT[S])Q.push(P(S,RT[S],A.d[S]+Tr[RT[S]].v));
		for(;k--;){
			if(Q.empty())return -1;
			u=Q.top();Q.pop();
			if(x=mg(Tr[u.y].l,Tr[u.y].r))Q.push(P(u.x,x,Tr[x].v-Tr[u.y].v+u.z));
			if(RT[x=Tr[u.y].y])Q.push(P(x,RT[x],u.z+Tr[RT[x]].v));
		}
		return u.z;
	}
}G;
int main(){
	G.init();
	printf("%d\n",G.work());
}

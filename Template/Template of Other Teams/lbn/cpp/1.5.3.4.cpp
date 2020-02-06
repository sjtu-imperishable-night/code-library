#include<bits/stdc++.h>//有源汇有上下界最小费用最大流 
#define N 111
#define M 22222
#define inf 1e9
#define CL(a) memset(a,0,sizeof a)
using namespace std;
int n,m,S,T,SS,TT;
struct CostFlow{
	int h,t,tot,an,fl,SUM,du[N],fir[N],va[M],la[M],ne[M],q[N],d[N],fa[N],pre[N],co[M];bool v[N];
	void in(){CL(fir);CL(pre);CL(fa);CL(du);tot=1;SUM=0;}//初始化
	void ins(int x,int y,int fl,int z){
		la[++tot]=y;ne[tot]=fir[x];va[tot]=fl;co[tot]=z;fir[x]=tot;
		la[++tot]=x;ne[tot]=fir[y];va[tot]=0;co[tot]=-z;fir[y]=tot;
	}
	void add(int x,int y,int L,int R,int c){//加x到y，流量L~R，费用c的边
		du[x]-=L;du[y]+=L;
		ins(x,y,R-L,c);
	}
	void prepare(){//重构图
		for(int i=1;i<=n;i++){
			if(du[i]>0)ins(SS,i,du[i],0),SUM+=du[i];
			if(du[i]<0)ins(i,TT,-du[i],0);
		}
		ins(T,S,inf,0);
	}
	bool spfa(int S,int T,int n){
		int i,x,y;
		for(i=1;i<=n;i++)d[i]=inf;
		for(CL(v),d[S]=h=0,v[q[t=1]=S]=1;h^t;)
			for(i=fir[x=q[h=h%n+1]],v[x]=0;i;i=ne[i])
				if(d[x]+co[i]<d[y=la[i]]&&va[i]){
					d[y]=d[fa[y]=x]+co[pre[y]=i];
					if(!v[y])v[q[t=t%n+1]=y]=1;
				}
		return d[T]<inf;
	}
	void end(int S,int T){
		int i,p=inf;
		for(i=T;i!=S;i=fa[i])p=min(p,va[pre[i]]);fl+=p;
		for(i=T;i!=S;i=fa[i])va[pre[i]]-=p,va[pre[i]^1]+=p,an+=p*co[pre[i]];
	}
	int cal(int S,int T,int n){//跑最小费用最大流
		for(an=fl=0;spfa(S,T,n);end(S,T));
		return an;
	}
	int work(){//不合法返回-1,否则返回最小费用
		cal(SS,TT,n+2);
		if(fl!=SUM)return -1;else return an;
	}
}G;
int main(){
	int i,j,x,y,L,R,z;
	scanf("%d%d%d%d",&n,&m,&S,&T);
	G.in();SS=n+1;TT=n+2;
	for(i=1;i<=m;i++)scanf("%d%d%d%d%d",&x,&y,&L,&R,&z),G.add(x,y,L,R,z);
	G.prepare();
	printf("%d\n",G.work());
}

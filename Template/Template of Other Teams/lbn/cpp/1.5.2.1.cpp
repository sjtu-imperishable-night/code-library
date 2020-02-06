#include<bits/stdc++.h>
#define N 444
#define M 44444
#define inf 1e9
#define CL(a) sizeof(a,0,sizeof a)
using namespace std;
struct CostFlow{
	int h,t,tot,fl,an,fir[N],va[M],la[M],ne[M],q[N],d[N],fa[N],pre[N],co[M];bool v[N];	
	void in(){CL(fir);CL(pre);CL(fa);tot=1;}//初始化，每次求解前都要调用
	void ins(int x,int y,int fl,int z){//加入一条x到y流量为fl费用为z的边
		la[++tot]=y;ne[tot]=fir[x];va[tot]=fl;co[tot]=z;fir[x]=tot;
		la[++tot]=x;ne[tot]=fir[y];va[tot]=0;co[tot]=-z;fir[y]=tot;
	}
	void init(){//将点数n、起点S和终点T读入，可以写在外面
		//int i,x,y,z,V;
		//scanf("%d%d%d%d",&n,&m,&S,&T);
		//for(i=1;i<=m;i++)scanf("%d%d%d%d",&x,&y,&z,&V),ins(x,y,z,V);
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
	pair<int,int> cal(int S,int T,int n){//给定起点S、终点T和点数n，得到流量和答案，注意答案有时会要用long long
		for(an=fl=0;spfa(S,T,n);end(S,T));
		return make_pair(fl,an);
	}
}G;
int main(){
	G.in();
	G.init();
//	printf("%d\n",G.cal());
}

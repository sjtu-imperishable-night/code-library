#include<bits/stdc++.h>
#define N 222222
#define M 888888
#define LL long long
using namespace std;
int n,m,i,scc,x,y,z,tot,to[N],fir[N],ne[M],la[M];
void ins_new(int x,int y){la[++tot]=y;ne[tot]=fir[x];fir[x]=tot;}//添加新边
struct Tarjan{//点双联通分量缩点
	int n,id,t,low[N],dfn[N],q[N];
	vector<int>V[N];
	void ins(int x,int y){V[x].push_back(y);}
	void in(int o){//初始化，新建点标号从n+1开始
		id=0;scc=o;
		for(int i=1;i<=o;i++)V[i].clear(),dfn[i]=low[i]=0;
	}
	void init(){//读入n个点m条边的无向图,注意记录n
		int i,x,y,m;
		scanf("%d%d",&n,&m);
		for(i=1;i<=m;i++)scanf("%d%d",&x,&y),ins(x,y),ins(y,x);
	}	
	void tj(int x,int fa){
		dfn[x]=low[x]=++id;q[++t]=x;int i,y,o;
		for(i=0;i<V[x].size();i++)if(!dfn[y=V[x][i]]){
			tj(y,x);low[x]=min(low[x],low[y]);
			if(low[y]>=dfn[x])for(ins_new(x,++scc),o=0;y!=o;)to[o=q[t--]]=scc,ins_new(scc,o);
		}else if(y!=fa)low[x]=min(low[x],dfn[y]);
	}
	void work(){//求解
		for(int i=1;i<=n;i++)if(!dfn[i])tj(i,0);	
	}
}G;
int main(){
	scanf("%d%d",&n,&m);G.in(n);
	for(i=1;i<=m;i++)scanf("%d%d",&x,&y),G.ins(x,y),G.ins(y,x);
	G.work();
}

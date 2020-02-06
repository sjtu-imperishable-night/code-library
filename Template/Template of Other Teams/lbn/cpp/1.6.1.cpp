#include<bits/stdc++.h>
#define N 1111111
#define M 1111111
using namespace std;
int tot,fir[N],ne[M],la[M];
void ins_new(int x,int y){la[++tot]=y;ne[tot]=fir[x];fir[x]=tot;}//缩点后的图建边
struct Tarjan{
	int n,id,t,scc,low[N],dfn[N],bl[N],q[N];bool is[N];	
	vector<int>V[N];
	void ins(int x,int y){V[x].push_back(y);}
	void in(int o){id=scc=0;for(int i=1;i<=o;i++)V[i].clear(),dfn[i]=low[i]=is[i]=bl[i]=0;}//初始化
	void init(){//读入点数、边数和每条边
		int i,x,y,m;
		scanf("%d%d",&n,&m);
		for(i=1;i<=m;i++)scanf("%d%d",&x,&y),ins(x,y);
	}	
	void tj(int x){//tarjan
		int i,y,o=0,E=V[x].size();
		low[x]=dfn[x]=++id;is[x]=1;q[++t]=x;		
		for(i=0;i<E;i++)
			if(!dfn[y=V[x][i]])tj(y),low[x]=min(low[x],low[y]);
			else if(is[y])low[x]=min(low[x],dfn[y]);
		if(dfn[x]==low[x])for(scc++;o!=x;o=q[t--],bl[o]=scc,is[o]=0);
	}
	void work(){//求解
		for(int i=1;i<=n;i++)if(!dfn[i])tj(i);	
	}
	void rebuild(){//缩点
		int x,y,i;bool mark[N];
		for(x=1;x<=n;x++){
			for(i=0;i<V[x].size();i++)
				if(y=V[x][i],bl[x]!=bl[y]&&!mark[bl[y]])
					mark[bl[y]]=1,ins_new(bl[x],bl[y]);
			for(i=0;i<V[x].size();i++)if(bl[x]!=bl[y])mark[y]=0;
		}
	}
	void out(){
		for(int i=1;i<=n;i++)printf("%d ",bl[i]);	
	}
}G;
int main(){
	G.init();
	G.work();
	G.rebuild();
	G.out();
}

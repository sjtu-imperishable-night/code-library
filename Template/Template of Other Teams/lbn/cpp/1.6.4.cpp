#include<bits/stdc++.h>
#define N 111111
using namespace std;
long long an[N];
struct Dominator_Tree{//新图中用dfn标号，semi/idom[dfn[x]]即为semi/idom[x]
	int n,s,cnt;//dom为支配树，标号为原图标号
	int dfn[N],id[N],pa[N],semi[N],idom[N],p[N],mn[N];
	vector<int>e[N],dom[N],be[N];
	void ins(int x,int y){e[x].push_back(y);}
	void in(){//读入点数n、边数m和起点s，在结构体里记录n和s
		int x,y,i,m;
		scanf("%d%d%d",&n,&m,&s);
		for(i=1;i<=n;i++)e[i].clear(),be[i].clear();cnt=0;
		for(i=1;i<=m;i++)scanf("%d%d",&x,&y),ins(x,y);
	}
	void dfs(int x){//先得到DFS树
		dfn[x]=++cnt;id[cnt]=x;
		for(auto i:e[x]){
			if(!dfn[i])dfs(i),pa[dfn[i]]=dfn[x];
			be[dfn[i]].push_back(dfn[x]);
		}
	}
	int get(int x){//带权并查集
		if(p[x]!=p[p[x]]){
			if(semi[mn[x]]>semi[get(p[x])])mn[x]=get(p[x]);
			p[x]=p[p[x]];
		}
		return mn[x];
	}
	void LT(){//求出semi和idom得到支配树
		for(int i=cnt;i>1;i--){
			for(auto j:be[i])semi[i]=min(semi[i],semi[get(j)]);
			dom[semi[i]].push_back(i);
			int x=p[i]=pa[i];
			for(auto j:dom[x])
				idom[j]=(semi[get(j)]<x?get(j):x);
			dom[x].clear();
		}
		for(int i=2;i<=cnt;i++){
			if(idom[i]!=semi[i])idom[i]=idom[idom[i]];
			dom[id[idom[i]]].push_back(id[i]);
		}
	}
	void build(){//建立支配树
		for(int i=1;i<=n;i++){//初始化
			dfn[i]=0;dom[i].clear();be[i].clear();
			p[i]=mn[i]=semi[i]=i;
		}
		cnt=0;dfs(s);LT();
	}
}G;
int main(){
	G.in();
	G.build();
}

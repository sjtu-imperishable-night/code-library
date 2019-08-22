#include<bits/stdc++.h>
#define N 2222
#define M 222222
#define inf 1e9
#define CL(a) memset(a,0,sizeof a)
int n,m,i,x,y,z,S,T,t,q[N];bool vv[N];
using namespace std;
struct MaxFlow{
	int tot,w,fir[N],cur[N],pre[N],d[N],nb[N],va[M],la[M],ne[M];
	void in(){tot=1;CL(fir);CL(d);CL(nb);CL(pre);}//注意每次求都要调用
	void ins(int x,int y,int z){
		la[++tot]=y;ne[tot]=fir[x];fir[x]=tot;va[tot]=z;
		la[++tot]=x;ne[tot]=fir[y];fir[y]=tot;va[tot]=0;
	}
	int flow(int S,int T,int n){//给定起点、终点和点数，求最大流
		int i,u, V,fl=0;
		for(i=1;i<=n;i++)cur[i]=fir[i];
		for(u=S,nb[0]=n;d[S]<n;){
			if(u==T){
				for(V=1e9,i=S;i!=T;i=la[cur[i]])
					if(va[cur[i]]<V)V=va[cur[u=i]];
				for(fl+=V,i=S;i!=T;i=la[cur[i]])
					va[cur[i]]-=V,va[cur[i]^1]+=V;
			}
			for(i=cur[u];i;i=ne[i])
				if(va[i]&&d[la[i]]+1==d[u])break;
			if(i)cur[u]=i,pre[la[i]]=u,u=la[i];else{
				if(!--nb[d[u]])break;
				for(i=cur[u]=fir[u],w=T;i;i=ne[i])
					if(d[la[i]]<w&&va[i])w=d[la[i]];
				++nb[d[u]=w+1];
				if(u!=S)u=pre[u];
			}
		}
		return fl;
	}
	void dfs(int x){//找在最小割S集中的点
		if(vv[x])return;vv[x]=1;
		for(int i=fir[x];i;i=ne[i])if(va[i])dfs(la[i]);
	}
}G;
int main(){
	scanf("%d%d",&n,&m);
	G.in();S=1;T=n;
	for(i=1;i<=m;i++)scanf("%d%d%d",&x,&y,&z),G.ins(x,y,z);
	printf("%d ",G.flow(S,T,n));
	G.dfs(S);
	for(i=1;i<=n;i++)if(vv[i])q[++t]=i;
	sort(q+1,q+t+1);
	printf("%d\n",t);
	for(i=1;i<=t;i++)printf("%d%c",q[i],i==t?'\n':' ');
}

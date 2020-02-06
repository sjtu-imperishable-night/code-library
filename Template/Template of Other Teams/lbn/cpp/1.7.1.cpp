#include<bits/stdc++.h>
#define N 111111
#define CL(a) memset(a,0,sizeof a)
using namespace std;
struct Fenzhi{
	int n,tot,rt,fir[N],ne[N*2],la[N*2],va[N*2],sz[N],mv[N];
	vector<int>V[N];bool vis[N];
	void in(){//初始化
		CL(fir);CL(vis);tot=0;
		for(int i=1;i<=n;i++)V[i].clear();
	}
	void ins(int x,int y){la[++tot]=y;ne[tot]=fir[x];fir[x]=tot;}
	void ins(int x,int y,int z){la[++tot]=y;ne[tot]=fir[x];fir[x]=tot;va[tot]=z;}
	void INS(int x,int y){V[x].push_back(y);}//分治树中的边
	void init(){
		int i,x,y;
		scanf("%d",&n);
		for(i=1;i<n;i++)scanf("%d%d",&x,&y),ins(x,y),ins(y,x);
	}
	void dsz(int x,int fa){
		sz[x]=1;mv[x]=0;
		for(int i=fir[x],y;i;i=ne[i])
			if(!vis[y=la[i]]&&y!=fa)
				dsz(y,x),sz[x]+=sz[y],mv[x]=max(mv[x],sz[y]);
	}
	void drt(int zs,int x,int fa,int&rt){//DFS两遍得到重心
		mv[x]=max(mv[x],sz[zs]-sz[x]);
		if(mv[x]<mv[rt]||!rt)rt=x;
		for(int i=fir[x],y;i;i=ne[i])
			if(!vis[y=la[i]]&&y!=fa)drt(zs,y,x,rt);
	}
	int fz(int x){//分治x点所在未选的子树
		int i,p,y,rt=0;dsz(x,0);drt(x,x,0,rt);vis[rt]=1;
		//ans+=calc(rt,0);
		for(i=fir[rt];i;i=ne[i])if(!vis[y=la[i]]){
			//ans-=calc(y,va[i]);
			INS(rt,fz(y));
		}
		return rt;
	}
	void work(){
		rt=fz(1);
	}
}G;
int main(){
	G.init();
	G.work();	
}

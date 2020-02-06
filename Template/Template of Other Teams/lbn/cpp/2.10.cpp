#include<bits/stdc++.h>
#define N 100100
using namespace std;
int fir[N],ne[N*2],la[N*2],sz[N],F[N],h[N],hs[N],bl[N],st[N];
void ins(int x,int y){la[++tot]=y;ne[tot]=fir[x];fir[x]=tot;}
void dfs(int x){//第一遍DFS
	sz[x]=1;int i,y;
	for(i=fir[x];i;i=ne[i])if(F[x]!=la[i]){
		F[y=la[i]]=x,h[y]=h[x]+1,dfs(y),sz[x]+=sz[y];
		if(sz[y]>sz[hs[x]])hs[x]=y;
	}
}
void dfs2(int x,int f){//第二遍DFS
	st[x]=++id;bl[x]=f;if(hs[x])dfs2(hs[x],f);
	for(int i=fir[x];i;i=ne[i])if(F[x]!=la[i]&&la[i]!=hs[x])dfs2(la[i],la[i]);
}
void add(int x,int y,int z){//在x~y这条链上+z
	for(;bl[x]!=bl[y];add(1,1,n,st[F[x]],st[x],z),x=F[bl[x]])
		if(h[bl[x]]<h[bl[y]])swap(x,y);
	if(h[x]<h[y])swap(x,y);
	add(1,1,n,st[y],st[x],z);
}
int qu(int x,int y){//询问x~y的和/最大值
	int V=0;
	for(;bl[x]!=bl[y];V+=qu(1,1,n,st[F[x]],st[x]),x=F[bl[x]])
		if(h[bl[x]]<h[bl[y]])swap(x,y);
	if(st[x]<st[y])swap(x,y);
	V+=qu(1,1,n,st[y],st[x]);
	return V;
}
int main(){
	scanf("%d%d",&n,&m);
	for(i=1;i<n;i++)scanf("%d%d",&x,&y),ins(x,y),ins(y,x);
	bd(1,1,n);//注意按DFS序建树
}

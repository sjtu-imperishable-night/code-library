#include<bits/stdc++.h>//SHOI仙人掌图，求仙人掌直径
#define N 555555
using namespace std;
int n,m,k,h,t,x,y,w,o,id,tot,ans,f[N],d[N],dfn[N],low[N],fa[N],fir[N],q[N],a[N],ne[N<<2],la[N<<2];
void ins(int x,int y){la[++tot]=y;ne[tot]=fir[x];fir[x]=tot;}
void get(int x,int y){
	int i;w=o=d[y]-d[x]+1;q[h=t=1]=1;
	for(i=y;i!=x;i=fa[i])a[w]=a[w+o]=f[i],w--;a[1]=a[1+o]=f[x];
	for(i=2;i<=o*2;q[++t]=i++){
		if(i-q[h]>(o/2))h++;
		for(ans=max(ans,a[i]+i+a[q[h]]-q[h]);h<=t&&a[i]-i>=a[q[t]]-q[t];t--);
	}
	for(i=2;i<=o;i++)f[x]=max(f[x],a[i]+min(i-1,o-i+1));
}
void dfs(int x){
	dfn[x]=low[x]=++id;int i,y;
	for(i=fir[x];i;i=ne[i])if(la[i]!=fa[x]){
		if(!dfn[y=la[i]])fa[y]=x,d[y]=d[x]+1,dfs(y);
		low[x]=min(low[x],low[y]);
		if(low[y]>dfn[x])ans=max(ans,f[y]+f[x]+1),f[x]=max(f[x],f[y]+1);
	}
	for(i=fir[x];i;i=ne[i])if(fa[la[i]]!=x&&dfn[x]<dfn[la[i]])get(x,la[i]);
}
int main(){
	for(scanf("%d%d",&n,&m);m--;)for(scanf("%d",&k),y=0;k--;y=x){scanf("%d",&x);if(y)ins(x,y),ins(y,x);}
	dfs(1);printf("%d",ans);
}

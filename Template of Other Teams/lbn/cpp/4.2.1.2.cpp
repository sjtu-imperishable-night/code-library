#include<bits/stdc++.h>// POI2015 Modernizacja autostrady
#define N 500300
using namespace std;
int n,i,A,Y,x,y,tot,fir[N],ne[N<<1],la[N<<1],f[N],g[N],h[N],u[N],f2[N],f1[N],g2[N],g3[N],fa[N];
void ins(int x,int y){la[++tot]=y;ne[tot]=fir[x];fir[x]=tot;}
int G(int x){return x?max(max(f[x],h[x]),(f[x]+1)/2+(h[x]+1)/2+1):1e9;}
int H(int x){return f[x]+h[x]+1;}
void dfs(int x){
	f1[x]=f2[x]=g2[x]=g3[x]=-1e9;f[x]=g[x]=0;
	for(int i=fir[x],y;i;i=ne[i])if(la[i]!=fa[x]){
		fa[y=la[i]]=x;dfs(y=la[i]),f[x]=max(f[x],max(f[y],g[x]+g[y]+1));
		if(f[y]>f1[x])f2[x]=f1[x],f1[x]=f[y];else f2[x]=max(f2[x],f[y]);
		if(g[y]+1>g[x])g3[x]=g2[x],g2[x]=g[x],g[x]=g[y]+1;
		else if(g[y]+1>g2[x])g3[x]=g2[x],g2[x]=g[y]+1;else g3[x]=max(g3[x],g[y]+1);
	}
}
void dfs2(int x){
	for(int i=fir[x],y,X,Y;i;i=ne[i])if(la[i]!=fa[x]){
		if(g[x]==g[y=la[i]]+1)X=g2[x],Y=g2[x]+g3[x];
		else if(g2[x]==g[y]+1)X=g[x],Y=g[x]+g3[x];else X=g[x],Y=g[x]+g2[x];
		h[y]=max(max(f1[x]==f[y]?f2[x]:f1[x],h[x]),max(X+u[x],Y));
		u[y]=max(X+1,u[x]+1);dfs2(y);
	}
}
int get(int x,int z){
	for(int i=fir[x],y;i;i=ne[i])if(la[i]!=fa[x])if(f[y=la[i]]==z)return get(y,z);
	return x;
}
int cal(int x,int z){
	if(g[x]-(z-g[x])<=1)return x;
	for(int i=fir[x],y;i;i=ne[i])if(la[i]!=fa[x])if(g[y=la[i]]+1==g[x])return cal(y,z);
}
int U(int x,int z){
	for(int i=fir[x],y;i;i=ne[i])if(la[i]!=fa[x])if(g[y=la[i]]+1==g[x])return U(y,z);
	return x;
}
int fd(int x,int F){
	memset(fa,0,sizeof(fa));fa[x]=F;dfs(x);
	return cal(get(x,f[x]),f[x]);
}
int df(int x,int F){
	memset(fa,0,sizeof(fa));fa[x]=F;dfs(x);
	return U(get(x,f[x]),f[x]);
}
int main(){
	for(scanf("%d",&n),i=1;i<n;i++)scanf("%d%d",&x,&y),ins(x,y),ins(y,x);
	for(dfs(1),dfs2(1),i=2;i<=n;i++)if(G(i)<G(A))A=i;Y=fa[A];
	printf("%d %d %d ",G(A),A,fa[A]);printf("%d %d\n",fd(A,Y),fd(Y,A));
	for(dfs(1),dfs2(1),i=2;i<=n;i++)if(H(i)>H(A))A=i;Y=fa[A];
	printf("%d %d %d ",H(A),A,Y);printf("%d %d\n",df(A,Y),df(Y,A));
}

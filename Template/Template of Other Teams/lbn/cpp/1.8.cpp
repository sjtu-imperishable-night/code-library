#include<bits/stdc++.h>
#define N 1001000
using namespace std;typedef long long LL;LL A,g[N];bool v[N],V[N];
int T,m,n,x,y,i,tot,id,ed,t,A1,A2,a[N],q[N],mi[N],mx[N],fir[N],st[N],d[N],f[N],F[N][20],ne[N<<1],la[N<<1],en[N];
bool cmp(int x,int y){return st[x]<st[y];}
void ins(int x,int y){if(x!=y)la[++tot]=y,ne[tot]=fir[x],fir[x]=tot;}
void dfs(int x,int fa){
	st[x]=++id;int i,y;for(i=1;i<=19;i++)F[x][i]=F[F[x][i-1]][i-1];
	for(i=fir[x];i;i=ne[i])if(la[i]!=fa)d[y=la[i]]=d[x]+1,F[y][0]=x,dfs(y,x);en[x]=id;
}
int lca(int x,int y){
	if(d[x]<d[y])swap(x,y);int t=d[x]-d[y],i;
	for(i=0;i<=19;i++)if(t>>i&1)x=F[x][i];
	for(i=19;i>=0;i--)if(F[x][i]!=F[y][i])x=F[x][i],y=F[y][i];
	return x==y?x:F[x][0];
}
void dfs(int x){//求解
	f[x]=V[x];g[x]=0;mi[x]=V[x]?0:1e9;mx[x]=V[x]?0:-1e9;
	for(int i=fir[x],y,o;i;i=ne[i])
		dfs(y=la[i]),o=d[y]-d[x],
		A+=(g[x]+1ll*f[x]*o)*f[y]+g[y]*f[x],
		f[x]+=f[y],g[x]+=g[y]+1ll*f[y]*o,
		A1=min(A1,mi[x]+mi[y]+o),A2=max(A2,mx[x]+mx[y]+o),
		mi[x]=min(mi[x],mi[y]+o),mx[x]=max(mx[x],mx[y]+o);
}
int main(){
	for(scanf("%d",&n),i=1;i<n;i++)scanf("%d%d",&x,&y),ins(x,y),ins(y,x);
	dfs(1,0),memset(fir,0,sizeof(fir));//DFS后将边表清空
	for(scanf("%d",&T);T--;){
		scanf("%d",&m),A=tot=0,A1=1e9,A2=-1e9;//初始化
		v[1]=a[1]=1,t=++m;//将1号点直接加入虚树
		for(i=2;i<=m;i++)scanf("%d",&a[i]),v[a[i]]=V[a[i]]=1;//v[]表示是选的点或选的点LCA后的点，V[]表示选的点
		for(sort(a+1,a+m+1,cmp),i=1;i<m;i++)if(!v[x=lca(a[i],a[i+1])])v[a[++t]=x]=1;//新加必要的关键点
		for(m=t,sort(a+1,a+m+1,cmp),ed=0,q[t=1]=1,i=2;i<=m;ins(q[t],a[i]),q[++t]=a[i++])//再排一遍序，用单调栈建虚树
			for(;st[a[i]]<st[q[t]]||en[a[i]]>en[q[t]];t--);
		for(dfs(i=1),printf("%lld %d %d\n",A,A1,A2);i<=m;i++)v[a[i]]=V[a[i]]=fir[a[i]]=0;//求解答案，然后还原
	}
}

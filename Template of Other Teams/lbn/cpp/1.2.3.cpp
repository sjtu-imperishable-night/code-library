#include<bits/stdc++.h>
#define N 1111
#define M 222222
#define inf 1e9
using namespace std;
int n,m,k,i,j,x,y,z,V,u,an,miv,cnt,F[N],a[N][N],mi[N],to[N];
bool e[N][N];
struct P{int x,y,z;}p[M],dp[N];
bool cmp(P a,P b){return a.z<b.z;}
void init(){
	scanf("%d%d%d%d",&n,&m,&k,&V);//n为点数,m为边数,k为度限制,V为限制点
	for(i=1;i<=n;i++)for(j=1;j<=n;j++)a[i][j]=inf;
	for(i=1;i<=m;i++){
		scanf("%d%d%d",&x,&y,&z);//读入每条边
		p[i].x=x;p[i].y=y;p[i].z=z;
		a[x][y]=a[y][x]=min(a[x][y],z);
	}
}
int fd(int x){return F[x]==x?x:F[x]=fd(F[x]);}
void Kruskal(){//先去除点V求若干最小生成树
	for(i=1;i<=n;i++)F[i]=i;
	sort(p+1,p+m+1,cmp);
	for(i=1;i<=m;i++){
		if(p[i].x==V||p[i].y==V)continue;
		x=fd(p[i].x);y=fd(p[i].y);
		if(x!=y){
			F[x]=y;
			e[p[i].x][p[i].y]=e[p[i].y][p[i].x]=1;
			an+=p[i].z;
		}
	}
}
void solve1(){//计算最小m度限制生成树
	for(i=1;i<=n;i++)mi[i]=inf;
	for(i=1;i<=n;i++)if(i!=V&&a[V][i]!=inf){//每个联通块中取一个和V连接的最小的
		x=fd(i);
		if(a[i][V]<mi[x])mi[x]=a[i][V],to[x]=i;
	}
	for(i=1;i<=n;i++)if(mi[i]!=inf){
		cnt++;
		e[V][to[i]]=e[to[i]][V]=1;
		an+=a[V][to[i]];
	}
}
void dfs(int x,int fa){//使用DP加速
	for(int i=1;i<=n;i++)if(i!=V&&e[x][i]&&i!=fa){
		if(dp[i].z==-1){
			if(a[x][i]<dp[x].z)dp[i]=dp[x];
			else dp[i].x=x,dp[i].y=i,dp[i].z=a[x][i];
		}
		dfs(i,x);
	}
}
void solve2(){//计算最小k度限制生成树
	for(i=cnt+1;i<=k;i++){
		memset(dp,-1,sizeof(dp));dp[1].z=-inf;
		for(j=1;j<=n;j++)if(e[V][j])p[j].z=-inf;
		dfs(V,0);u=0;miv=inf;
		for(j=1;j<=n;j++)if(a[V][j]!=inf&&a[V][j]-dp[j].z<miv){//找一个最小的
			miv=a[V][j]-dp[j].z;
			u=j;
		}
		if(miv>=0)break;//如果w(T)不能变得更小，那么结束
		x=dp[u].x,y=dp[u].y;
		e[V][u]=e[u][V]=1;
		e[x][y]=e[y][x]=0;//更改T并更新答案
		an+=miv;
	}
}
int main(){
	init();
	Kruskal();
	solve1();
	solve2();
	printf("%d",an);
}

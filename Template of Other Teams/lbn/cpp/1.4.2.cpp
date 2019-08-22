#include<bits/stdc++.h>
#define inf 1e9//不存在的边权开到-n*(|maxv|+1),inf为3n*(|maxv|+1)
#define N 404
#define CL(a,b) memset(a,b,sizeof a)
using namespace std;long long ans;
int n,py,m,x,y,i,j,d,p,lx[N],ly[N],w[N][N],lk[N],slk[N],pre[N];
bool vy[N];
int main(){
	scanf("%d",&n);
	for(i=1;i<=n;i++)for(j=1;j<=n;j++)scanf("%d",&w[i][j]),lx[i]=max(lx[i],w[i][j]);
	for(i=1;i<=n;i++){
		for(j=1;j<=n;j++)slk[j]=inf,vy[j]=0;
		for(lk[py=0]=i;lk[py];py=p){
			vy[py]=1;d=inf;x=lk[py];
			for(y=1;y<=n;y++)if(!vy[y]){
				if(lx[x]+ly[y]-w[x][y]<slk[y])slk[y]=lx[x]+ly[y]-w[x][y],pre[y]=py;
				if(slk[y]<d) d=slk[y],p=y;
			}
			for(y=0;y<=n;y++)if(vy[y])lx[lk[y]]-=d,ly[y]+=d;else slk[y]-=d;
		}
		for(;py;py=pre[py])lk[py]=lk[pre[py]];
  	}
	for(i=1;i<=n;i++)ans+=lx[i]+ly[i];
	printf("%lld\n",ans);
	for(i=1;i<=n;i++)printf("%d %d\n",lk[i],i);
}

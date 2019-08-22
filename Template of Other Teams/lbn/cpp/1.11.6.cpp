#include<bits/stdc++.h>
#define N 155
using namespace std;
int n,m,i,j,x,y,an,q[N][N],ce[N],ne[N];
bool g[N][N];
void dfs(int p){
	int i,j,k,t,cnt,mv;
	if(ne[p]==ce[p]){
		if(!ce[p])an++;
		return;
	}
	for(t=0,i=1;i<=ne[p];i++){
		for(cnt=0,j=ne[p]+1;j<=ce[p];j++)
			if(!g[q[p][i]][q[p][j]])cnt++;
		if(!t||cnt<mv)t=i,mv=cnt;
	}
	if(t&&mv<=0)return;
	for(k=ne[p]+1;k<=ce[p];k++){
		if(t>0){
			for(i=k;i<=ce[p];i++)if(!g[q[p][t]][q[p][i]])break;
			swap(q[p][k],q[p][i]);
		}
		i=q[p][k];ne[p+1]=ce[p+1]=0;
		for(j=1;j<k;j++)if(g[i][q[p][j]])q[p+1][++ne[p+1]]=q[p][j];
		for(ce[p+1]=ne[p+1],j=k+1;j<=ce[p];j++)
			if(g[i][q[p][j]])q[p+1][++ce[p+1]]=q[p][j];
		dfs(p+1);++ne[p];--mv;
		for(j=k+1,cnt=0;j<=ce[p];j++)if(!g[i][q[p][j]])cnt++;
		if(!t||cnt<mv)t=k,mv=cnt;
		if(t&&mv<=0)break;
	}
}
void cluster_counting(){
	int i;
	an=ne[0]=ce[0]=0;
	for(i=1;i<=n;i++)q[0][++ce[0]]=i;
	dfs(0);
}
int main(){//g[][]邻接矩阵，存图
	scanf("%d%d",&n,&m);
	for(i=1;i<=m;i++)scanf("%d%d",&x,&y),g[x][y]=g[y][x]=1;
	cluster_counting();
	printf("%d\n",an);
}

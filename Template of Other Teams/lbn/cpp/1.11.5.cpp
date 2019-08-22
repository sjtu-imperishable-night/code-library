#include<bits/stdc++.h>//求最大团，g[][]是邻接矩阵，存边
#define N 55
using namespace std;bool ff;
int n,i,j,an,mc[N],len[N],g[N][N],V[N][N];
void dfs(int p){
	int i,j,k;
	if(!len[p]){
		if(p>an)an=p,ff=1;
		return;
	}
	for(k=0;k<len[p]&&!ff;k++){
		if(p+len[p]-k<=an)break;
		i=V[p][k];
		if(p+mc[i]<=an)break;
		for(j=k+1,len[p+1]=0;j<len[p];j++)
			if(g[i][V[p][j]])V[p+1][len[p+1]++]=V[p][j];
		dfs(p+1);
	}
}
void work(){
	int i,j;
	mc[n]=an=1;
	for(i=n-1;i;i--){
		ff=0;len[1]=0;
		for(j=i+1;j<=n;j++)if(g[i][j])V[1][len[1]++]=j;
		dfs(1);mc[i]=an;
	}
}
int main(){
	for(;scanf("%d",&n),n;){
		for(i=1;i<=n;i++)for(j=1;j<=n;j++)scanf("%d",&g[i][j]);
		work();
		printf("%d\n",an);
	}
}

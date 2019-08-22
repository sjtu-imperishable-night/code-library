#include<bits/stdc++.h>//求无向图所有点对间的最小割，O(n^3)
#define N 505//和求固定源点任意汇点最小割相同
#define inf 1e9
#define CL(a) memset(a,0,sizeof a)
using namespace std;
int n,m,d[N],w[N][N];bool v[N],g[N];
int get(int&s,int&t){
	CL(d);CL(v);
	int i,j,k,an,mx;
	for(i=1;i<=n;i++){
		k=-1;mx=-1;
		for(j=1;j<=n;j++)if(!g[j]&&!v[j]&&d[j]>mx)k=j,mx=d[j];
		if(k==-1)return an;
		s=t;t=k;an=mx;v[k]=1;
		for(j=1;j<=n;j++)if(!g[j]&&!v[j])d[j]+=w[k][j];
	}
	return an;
}
int main(){
	int ans,i,j,s,t,x,y,z;
	scanf("%d%d",&n,&m);ans=inf;//读入点数n、边数m和若干条双向边(x,y,z)
	for(i=1;i<=m;i++)scanf("%d%d%d",&x,&y,&z),w[x][y]=(w[y][x]+=z);//输入每条边，注意重边情况
	for(i=1;i<n;i++){
		ans=min(ans,get(s,t));g[t]=1;
		if(!ans)break;
		for(j=1;j<=n;j++)if(!g[j])w[s][j]=(w[j][s]+=w[j][t]);
	}
	printf("%d\n",ans);
}

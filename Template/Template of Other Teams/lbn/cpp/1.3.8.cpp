#include<bits/stdc++.h>
#define N 62
#define M 2222
#define inf 1e9
using namespace std;
int T,tot,n,m,k,i,j,w,S,h,t,x,y,z,E,an,q[N],f[N][M],fir[N],ne[M],va[M],la[M];
bool v[N];
void ins(int x,int y,int z){la[++tot]=y;ne[tot]=fir[x];fir[x]=tot;va[tot]=z;}
int main(){
	scanf("%d%d%d",&n,&m,&k);E=(1<<k)-1;
	for(i=1;i<=n;i++)for(j=0;j<=E;j++)f[i][j]=inf;
	for(i=1;i<=m;i++)scanf("%d%d%d",&x,&y,&z),ins(x,y,z),ins(y,x,z);
	for(i=1;i<=k;i++)f[i][1<<(i-1)]=0;//默认1到k为要联通的点
	for(w=1;w<=E;w++){
		for(h=t=0,i=1;i<=n;i++)//DP转移
			for(S=w&(w-1);S;S=w&(S-1))
				f[i][w]=min(f[i][w],f[i][S]+f[i][w-S]);
		for(i=1;i<=n;i++)if(f[i][w]<inf)q[++t]=i,v[i]=1;
		for(;h^t;)//SPFA转移
			for(v[x=q[h=h%n+1]]=0,i=fir[x];i;i=ne[i])
				if(f[y=la[i]][w]>f[x][w]+va[i]){
					f[y][w]=f[x][w]+va[i];
					if(!v[y])v[q[t=t%n+1]=y]=1;
				}
	}
	for(an=inf,i=1;i<=n;i++)an=min(an,f[i][E]);
	printf("%d",an);
}

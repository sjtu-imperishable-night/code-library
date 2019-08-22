#include<bits/stdc++.h>
#define N 111111
#define M 222222
int n,i,x,y,z,t,tot,fir[N],F[N],cur[N],d[N],sz[N],q[N],la[M],ne[M],va[M];
void ins(int x,int y,int z){la[++tot]=y;ne[tot]=fir[x];fir[x]=tot;va[tot]=z;}
int main(){
	scanf("%d",&n);
	for(i=1;i<n;i++)scanf("%d%d%d",&x,&y,&z),ins(x,y,z),ins(y,x,z);
	for(i=1;i<=n;i++)cur[i]=fir[i];
	for(q[t=1]=sz[x]=1;t;){
		int x=q[t],y;
		for(;cur[x]&&la[cur[x]]==F[x];)cur[x]=ne[cur[x]];
		if(cur[x]){
			y=la[cur[x]];
			q[++t]=y;
			F[y]=x;
			sz[y]=1;
			d[y]=d[x]+va[cur[x]];
			cur[x]=ne[cur[x]];
		}else{
			t--;
			if(F[x]){
				sz[F[x]]+=sz[x];
			}
		}
	}
}

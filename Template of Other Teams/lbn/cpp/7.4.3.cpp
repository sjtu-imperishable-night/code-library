#include<bits/stdc++.h>//BZOJ2001
#define N 50005
#define inf 1e9
using namespace std;typedef long long LL;
int n,m,Q,i,w,o,u,v[N],to[N],F[N],R[N],nb[22];LL ans[N];
struct P{int x,y,z,id;}e[22][N],p[N],q[N];bool cmp(P a,P b){return a.z<b.z;}
int gf(int x){return F[x]==x?x:F[x]=gf(F[x]);}
void cdq(int d,int l,int r,LL z){
	int i,m=nb[d],mid=l+r>>1;if(l==r)v[q[l].x]=q[l].y;
	for(i=1;i<=m;i++)e[d][i].z=v[e[d][i].id],p[i]=e[d][i],to[p[i].id]=i,F[p[i].x]=p[i].x,F[p[i].y]=p[i].y;
	if(l==r){
		for(sort(p+1,p+m+1,cmp),i=1;i<=m;i++){
			o=gf(p[i].x);u=gf(p[i].y);
			if(o!=u)F[o]=u,z+=p[i].z;
		}
		ans[l]=z;return;
	}
	for(i=l;i<=r;i++)p[to[q[i].x]].z=-inf;
	for(sort(p+1,p+m+1,cmp),w=0,i=1;i<=m;i++){
		o=gf(p[i].x);u=gf(p[i].y);
		if(o!=u)F[o]=u,R[++w]=i;
	}
	for(i=1;i<=m;i++)F[p[i].x]=p[i].x,F[p[i].y]=p[i].y;
	for(i=1;i<=w;i++)if(p[R[i]].z!=-inf)z+=p[R[i]].z,F[gf(p[R[i]].x)]=gf(p[R[i]].y);
	for(nb[d+1]=0,i=1;i<=m;i++){
		p[i].x=gf(p[i].x);p[i].y=gf(p[i].y);
		if(p[i].z==-inf)p[i].z=inf,e[d+1][++nb[d+1]]=p[i];
	}
	for(sort(p+1,p+m+1,cmp),i=1;i<=m;i++){
		o=gf(p[i].x);u=gf(p[i].y);
		if(o!=u){
			F[o]=u;
			if(p[i].z!=inf)e[d+1][++nb[d+1]]=p[i];
		}
	}
	cdq(d+1,l,mid,z);cdq(d+1,mid+1,r,z);
}
int main(){
	for(scanf("%d%d%d",&n,&m,&Q),i=1;i<=m;i++)scanf("%d%d%d",&e[0][i].x,&e[0][i].y,&v[i]),e[0][i].id=i,e[0][i].z=v[i];
	for(nb[0]=m,i=1;i<=Q;i++)scanf("%d%d",&q[i].x,&q[i].y);
	for(cdq(0,1,Q,0),i=1;i<=Q;i++)printf("%lld\n",ans[i]);
}
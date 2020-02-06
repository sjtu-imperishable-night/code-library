#include<bits/stdc++.h>//三维偏序，条件为<=，最长不下降，未验
#define N 100100
using namespace std;
int n,i,an,cntx,cnty,cntz,vx[N],vy[N],vz[N],b[N],c[N];
struct P{int x,y,z,an;}p[N];
bool cmp(P a,P b){return a.x<b.x||a.x==b.x&&a.y<b.y||a.x==b.x&&a.y==b.y&&a.z<b.z;}
bool cmp2(P a,P b){return a.y<b.y||a.y==b.y&&a.z<b.z;}
void cg(int x){for(;x<=cntz;x+=x&-x)c[x]=0;}
void add(int x,int z){for(;x<=cntz;x+=x&-x)c[x]=max(c[x],z);}
int qu(int x){int v=0;for(;x;x-=x&-x)v=max(v,c[x]);return v;}
void solve(int l,int r){
	if(l==r){p[l].an=max(p[l].an,1);return;}
	int md=l+r>>1,i=1,j=md+1,k;
	solve(l,md);
	sort(p+1,p+md+1,cmp2);sort(p+md+1,p+r+1,cmp2);
	for(;j<=r;j++){
		for(;i<=md&&p[i].y<=p[j].y;i++)add(p[i].z,p[i].an);
		p[j].an=max(p[j].an,qu(p[j].z)+1);
	}
	for(j=l;j<i;j++)cg(p[j].z);
	sort(p+1,p+r+1,cmp);
	solve(md+1,r);
}
int main(){
	scanf("%d",&n);
	for(i=1;i<=n;i++)scanf("%d%d%d",&p[i].x,&p[i].y,&p[i].z),vx[i]=p[i].x,vy[i]=p[i].y,vz[i]=p[i].z;
	sort(vx+1,vx+n+1);cntx=unique(vx+1,vx+n+1)-vx-1;
	sort(vy+1,vy+n+1);cnty=unique(vy+1,vy+n+1)-vy-1;
	sort(vz+1,vz+n+1);cntz=unique(vz+1,vz+n+1)-vz-1;
	for(i=1;i<=n;i++){
		p[i].x=lower_bound(vx+1,vx+cntx+1,p[i].x)-vx;
		p[i].y=lower_bound(vy+1,vy+cnty+1,p[i].y)-vy;
		p[i].z=lower_bound(vz+1,vz+cntz+1,p[i].z)-vz;
	}
	sort(p+1,p+n+1,cmp);
	solve(1,n);
	for(i=1;i<=n;i++)an=max(an,p[i].an);
	printf("%d\n",an);
}

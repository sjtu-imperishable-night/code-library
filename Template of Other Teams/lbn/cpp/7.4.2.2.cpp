#include<bits/stdc++.h>//四维偏序，求i<j,Xi<Xj,Yi<Yj,Zi<Zj的对数 
#define N 100100
using namespace std;
int n,i,an,b[N],c[N];
struct P{int x,y,z,id,f;}p[N],q[N];
bool cmp(P a,P b){return a.x<b.x||a.x==b.x&&a.y>b.y||a.x==b.x&&a.y==b.y&&a.z>b.z;}
bool cmp2(P a,P b){return a.y<b.y||a.y==b.y&&a.z>b.z;}
void add(int x,int z){for(;x<=n;x+=x&-x)c[x]+=z;}
int qu(int x){int v=0;for(;x;x-=x&-x)v+=c[x];return v;}
void cdq2(int l,int r){
	if(l>=r)return;int md=l+r>>1;
	cdq2(l,md);cdq2(md+1,r);
	sort(q+l,q+md+1,cmp2);sort(q+md+1,q+r+1,cmp2);
	int i=l,j=md+1,k=l;
	for(;j<=r;j++){
		for(;i<=md&&q[i].y<q[j].y;i++)if(q[i].f)add(q[i].z,1);
		if(!q[j].f)an+=qu(q[j].z-1);
	}
	for(j=l;j<i;j++)if(q[j].f)add(q[j].z,-1);
}
void cdq1(int l,int r){
	if(l>=r)return;int md=l+r>>1;
	cdq1(l,md);cdq1(md+1,r);
	sort(p+l,p+md+1,cmp);sort(p+md+1,p+r+1,cmp);
	int i=l,j=md+1,k=l;
	for(;j<=r;p[j].f=0,q[k++]=p[j++])
		for(;i<=md&&p[i].x<p[j].x;q[k++]=p[i++])p[i].f=1;
	for(;i<=md;q[k++]=p[i++])p[i].f=1;
	cdq2(l,r);
}
int main(){
	scanf("%d",&n);
	for(i=1;i<=n;i++)scanf("%d",&p[i].x),p[i].id=i;
	for(i=1;i<=n;i++)scanf("%d",&p[i].y);
	for(i=1;i<=n;i++)scanf("%d",&p[i].z);
	cdq1(1,n);
	printf("%d\n",an);
}

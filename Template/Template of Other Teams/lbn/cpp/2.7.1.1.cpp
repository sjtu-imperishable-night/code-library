#include<bits/stdc++.h>
#define N 100100
#define M 2002000
using namespace std;
int n,m,i,x,y,k,id,cnt,T[N],a[N],v[N],L[M],R[M],sz[M];
void ins(int x,int&y,int l,int r,int z){
	sz[y=++id]=sz[x]+1;
	if(l==r)return;
	L[y]=L[x];R[y]=R[x];
	int md=l+r>>1;
	if(z<=md)ins(L[x],L[y],l,md,z);else ins(R[x],R[y],md+1,r,z);
}
int ask(int x,int y,int l,int r,int k){
	if(l==r)return l;
	int md=l+r>>1;
	if(k<=sz[L[y]]-sz[L[x]])return ask(L[x],L[y],l,md,k);
	else return ask(R[x],R[y],md+1,r,k-sz[L[y]]+sz[L[x]]);
}
int main(){
	scanf("%d%d",&n,&m);
    for(i=1;i<=n;i++)scanf("%d",&a[i]),v[i]=a[i];
	sort(v+1,v+n+1);cnt=unique(v+1,v+n+1)-v-1;
	for(i=1;i<=n;i++)ins(T[i-1],T[i],1,cnt,a[i]=lower_bound(v+1,v+cnt+1,a[i])-v);
	for(;m--;){
		scanf("%d%d%d",&x,&y,&k);
		printf("%d\n",v[ask(T[x-1],T[y],1,cnt,k)]);
	}
}
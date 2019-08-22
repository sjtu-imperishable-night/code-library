#include<bits/stdc++.h>//区间加和区间询问两个操作
#define N 100100
#define M 266666
#define LL long long
int n,m,i,l,r,z,a[N],sz[M];
char s[9];LL S[M],ad[M];
void ps(int k){S[k]=S[k<<1]+S[k<<1|1]+ad[k]*sz[k];}
void bd(int k,int l,int r){
	sz[k]=r-l+1; 
	if(l==r){S[k]=a[l];return;}
	int md=l+r>>1;
	bd(k<<1,l,md);bd(k<<1|1,md+1,r);
	ps(k);
}
void add(int k,int l,int r,int x,int y,int z){//区间修改
	if(x<=l&&r<=y){
		S[k]+=1ll*sz[k]*z;
		ad[k]+=z;
		return;
	}
	int md=l+r>>1;
	if(x<=md)add(k<<1,l,md,x,y,z);
	if(y>md)add(k<<1|1,md+1,r,x,y,z);
	ps(k);
}
LL qu(int k,int l,int r,int x,int y,int AD){//区间询问，AD为根到目前点的ad之和
	if(x<=l&&r<=y)return 1ll*AD*sz[k]+S[k];
	int md=l+r>>1;AD+=ad[k];
	if(x>md)return qu(k<<1|1,md+1,r,x,y,AD);
	if(y<=md)return qu(k<<1,l,md,x,y,AD);
	return qu(k<<1,l,md,x,y,AD)+qu(k<<1|1,md+1,r,x,y,AD);
}
int main(){
	scanf("%d%d",&n,&m);
	for(i=1;i<=n;i++)scanf("%d",&a[i]);
	bd(1,1,n);
	for(;m--;){
		scanf("%s%d%d",s,&l,&r);
		if(s[0]=='C')scanf("%d",&z),add(1,1,n,l,r,z);
		else printf("%lld\n",qu(1,1,n,l,r,0));
	}
}

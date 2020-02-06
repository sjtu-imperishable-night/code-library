#include<bits/stdc++.h>
#define L k<<1
#define R k<<1|1
#define LL long long
#define N 2222222
using namespace std;//mx[]最大值 mx2[]次大值 num[]最大值个数 S[]和
LL S[N];int T,n,m,i,lx,x,y,z,mx[N],mx2[N],num[N],a[N/2];
void ps(int k){
	S[k]=S[L]+S[R];num[k]=0;
	mx[k]=max(mx[L],mx[R]);mx2[k]=max(mx2[L],mx2[R]);
	if(mx[L]!=mx[R])mx2[k]=max(mx2[k],min(mx[L],mx[R]));
	if(mx[k]==mx[L])num[k]+=num[L];
	if(mx[k]==mx[R])num[k]+=num[R];
}
void bd(int k,int l,int r){
	if(l==r){S[k]=mx[k]=a[l];num[k]=1;mx2[k]=-1e9;return;}
	int md=l+r>>1;bd(L,l,md);bd(R,md+1,r);ps(k);
}
void CG(int k,int z){
	if(z>=mx[k])return;
	S[k]+=1ll*(z-mx[k])*num[k];
	mx[k]=z;
}
void pd(int k){CG(L,mx[k]);CG(R,mx[k]);}
void cg(int k,int l,int r,int x,int y,int z){//区间对z取min
	if(mx[k]<=z)return;
	if(x<=l&&r<=y&&z>mx2[k]){CG(k,z);return;}
	int md=l+r>>1;pd(k);
	if(x<=md)cg(L,l,md,x,y,z);
	if(y>md)cg(R,md+1,r,x,y,z);
	ps(k);
}
int qumx(int k,int l,int r,int x,int y){//区间取max
	if(x<=l&&r<=y)return mx[k];
	int md=l+r>>1,V=0;pd(k);
	if(x<=md)V=max(V,qumx(L,l,md,x,y));
	if(y>md)V=max(V,qumx(R,md+1,r,x,y));
	return V;
}
LL qus(int k,int l,int r,int x,int y){//区间求和
	if(x<=l&&r<=y)return S[k];
	int md=l+r>>1;LL V=0;pd(k);
	if(x<=md)V+=qus(L,l,md,x,y);
	if(y>md)V+=qus(R,md+1,r,x,y);
	return V;
}
int main(){
	for(scanf("%d",&T);T--;){
		scanf("%d%d",&n,&m);
		for(i=1;i<=n;i++)scanf("%d",&a[i]);
		for(bd(1,1,n);m--;){
			scanf("%d%d%d",&lx,&x,&y);
			if(!lx)scanf("%d",&z),cg(1,1,n,x,y,z);
			if(lx==1)printf("%d\n",qumx(1,1,n,x,y));
			if(lx==2)printf("%lld\n",qus(1,1,n,x,y));
		}
	}
}

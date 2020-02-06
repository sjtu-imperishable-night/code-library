#include<bits/stdc++.h>//SPOJ To The Moon 
#define LL long long
#define N 100100
#define M 10004000
int n,m,i,l,r,z,id,nv,a[N],T[N],L[M],R[M],sz[M];
LL S[M],ad[M];char s[9];
int ADD(int A,LL z){//用B复制A，在B上懒惰+z，并返回B 
	int B=++id;
	L[B]=L[A];R[B]=R[A];sz[B]=sz[A];
	ad[B]=ad[A]+z;S[B]=S[A]+z*sz[B];
	return B;
}
void pd(int k){//下传时改变左儿子和右儿子 
	if(ad[k])L[k]=ADD(L[k],ad[k]),R[k]=ADD(R[k],ad[k]),ad[k]=0;
}
void ps(int k){S[k]=S[L[k]]+S[R[k]];}
int bd(int l,int r){//建树 
	int k=++id;sz[k]=r-l+1;
	if(l==r)return S[k]=a[l],k;
	int md=l+r>>1;
	L[k]=bd(l,md);R[k]=bd(md+1,r);
	return ps(k),k;
}
int add(int A,int l,int r,int x,int y,int z){//区间+z 
	if(x<=l&&r<=y)return ADD(A,z);
	pd(A);int md=l+r>>1,B=++id;
	L[B]=L[A];R[B]=R[A];sz[B]=sz[A];S[B]=S[A];
	if(x<=md)L[B]=add(L[A],l,md,x,y,z);
	if(y>md)R[B]=add(R[A],md+1,r,x,y,z);
	return ps(B),B;
}
LL qu(int k,int l,int r,int x,int y){///询问区间和 
	if(!k)return 0;
	if(x<=l&&r<=y)return S[k];
	int md=l+r>>1;pd(k);
	if(x>md)return qu(R[k],md+1,r,x,y);
	if(y<=md)return qu(L[k],l,md,x,y);
	return qu(L[k],l,md,x,y)+qu(R[k],md+1,r,x,y);
}
int main(){
	scanf("%d%d",&n,&m);
	for(i=1;i<=n;i++)scanf("%d",&a[i]);
	for(T[0]=bd(1,n);m--;){
		scanf("%s",s);
		if(s[0]=='C')scanf("%d%d%d",&l,&r,&z),T[nv+1]=add(T[nv],1,n,l,r,z),nv++;//区间修改 
		if(s[0]=='Q')scanf("%d%d",&l,&r),printf("%lld\n",qu(T[nv],1,n,l,r));//询问当前答案 
		if(s[0]=='H')scanf("%d%d%d",&l,&r,&z),printf("%lld\n",qu(T[z],1,n,l,r));//询问历史答案 
		if(s[0]=='B')scanf("%d",&z),nv=z;//回到历史 
	}
}

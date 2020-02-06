#include<bits/stdc++.h>
#define LL long long
#define N 33333
using namespace std;vector<int>Q;int T,n,m,i,A[N],B[N],C[N],E[N];LL D[N],pre[N];
struct BIT{//树状数组区间更新区间求和
	LL a[N],b[N];int v[N];
	void ad(int x,LL z){
		for(int i=x;i<=n;i+=i&-i)
			if(v[i]<T)v[i]=T,a[i]=z,b[i]=z*(x-1);else a[i]+=z,b[i]+=z*(x-1);
	}
	LL qu(LL x){
		LL v0=0,v1=0;
		for(int i=x;i;i-=i&-i)if(v[i]==T)v0+=a[i],v1+=b[i];
		return x*v0-v1;
	}
	void add(int x,int y,LL z){ad(x,z);ad(y+1,-z);}
	LL sum(int x,int y){return qu(y)-qu(x-1);}
}b0,b1;
void solve(int l,int r,vector<int>Q){//Q的答案在[l,r]之间
	if(!Q.size())return;
	if(l==r){//递归到底更新答案
		for(int i=0;i<Q.size();i++)if(A[Q[i]]==2)E[Q[i]]=l;
		return;
	}
	int md=l+r>>1;vector<int>Ql,Qr;T++;//时间戳 
	for(int i=0;i<Q.size();i++){
		int x=Q[i],a=A[x],b=B[x],c=C[x],d=D[x],e=E[x];
		if(a==1){//统计修改的贡献
			if(d<=l&&r<=e)b0.add(b,c,1);else{
				int dd=max(d,l),ee=min(e,md);
				if(dd<=ee)b1.add(b,c,ee-dd+1);
				if(d<=md)Ql.push_back(x);
				if(e>md)Qr.push_back(x);
			}
		}else{//处理询问
			pre[x]+=b0.sum(b,c);
			LL p=pre[x]*(md-l+1)+b1.sum(b,c);
			if(p>=D[x])Ql.push_back(x);else D[x]-=p,Qr.push_back(x);
		}
	}
	solve(l,md,Ql);solve(md+1,r,Qr);//递归解决
}
int main(){
	scanf("%d%d",&n,&m);
	for(i=1;i<=m;i++){//A[i]=1在D[i]~E[i]每个位置加上B[i]~C[i]每个数，A[i]=2询问B[i]~C[i]的第D[i]大
		scanf("%d%d%d%lld",&A[i],&B[i],&C[i],&D[i]);
		if(A[i]==1)scanf("%d",&E[i]);
		Q.push_back(i);
	}
	solve(1,n,Q);
	for(i=1;i<=m;i++)if(A[i]==2)printf("%d\n",E[i]);
} 

#include<bits/stdc++.h>
#define N 500500
#define inf 1e9
using namespace std;
int rt,id,t,q[N*10],a[N],key[N],sz[N],L[N],R[N],lm[N],rm[N],mm[N],V[N],S[N],cv[N],fcv[N],rv[N];
int newnode(int z){//新建节点，值为z，返回点标 
	int x;
	if(t)x=q[t--];else x=++id;
	lm[x]=rm[x]=mm[x]=V[x]=S[x]=z;
	sz[x]=1;key[x]=rand();
	fcv[x]=cv[x]=rv[x]=L[x]=R[x]=0;
	return x;
}
void REV(int x){
	if(!x)return;
	swap(L[x],R[x]);
	swap(lm[x],rm[x]);
	rv[x]^=1;
}
void COV(int x,int z){
	if(!x)return;
	V[x]=z;S[x]=z*sz[x];
	lm[x]=rm[x]=mm[x]=max(V[x],S[x]);
	cv[x]=z;fcv[x]=1;
}
void pd(int x){
	if(fcv[x])COV(L[x],cv[x]),COV(R[x],cv[x]),fcv[x]=0;
	if(rv[x])REV(L[x]),REV(R[x]),rv[x]=0;
}
void ps(int x){
	int l=L[x],r=R[x];
	sz[x]=sz[l]+sz[r]+1;
	S[x]=S[l]+S[r]+V[x];
	lm[x]=max(lm[l],S[l]+V[x]+max(0,lm[r]));
	rm[x]=max(rm[r],S[r]+V[x]+max(0,rm[l]));
	mm[x]=max(max(mm[l],mm[r]),max(0,rm[l])+V[x]+max(0,lm[r]));
}
int merge(int x,int y){
	if(!x||!y)return x+y;int z=0;
	if(key[x]>key[y])pd(y),z=y,L[z]=merge(x,L[y]);
	else pd(x),z=x,R[z]=merge(R[x],y);
	ps(z);return z;
}
void split(int x,int&y,int&z,int k){
	y=z=0;if(!x)return;pd(x);
	if(sz[L[x]]>=k)z=x,split(L[x],y,L[z],k),ps(z);
	else y=x,split(R[x],R[y],z,k-sz[L[x]]-1),ps(y);
}
void recycle(int x){//回收 
	if(!x)return;
	q[++t]=x;
	recycle(L[x]);
	recycle(R[x]);
}
void insert(int x,int z){//在x位置插入一个数 
	int A,B;
	split(rt,A,B,x);
	rt=merge(merge(A,newnode(z)),B);
}
void del(int l,int r){//删除一段数[l,r] 
	int A,AA,B,C;
	split(rt,A,AA,l-1);
	split(AA,B,C,r-l+1);
	recycle(B);
	rt=merge(A,C);
}
void cov(int l,int r,int z){//将[l,r]赋值为z 
	int A,AA,B,C;
	split(rt,A,AA,l-1);
	split(AA,B,C,r-l+1);
	COV(B,z);
	rt=merge(merge(A,B),C);
}
void rev(int l,int r){//将区间[l,r]翻转 
	int A,AA,B,C;
	split(rt,A,AA,l-1);
	split(AA,B,C,r-l+1);
	REV(B);
	rt=merge(merge(A,B),C);
}
int qusum(int l,int r){//询问[l,r]的和 
	int A,AA,B,C,an;
	split(rt,A,AA,l-1);
	split(AA,B,C,r-l+1);
	an=S[B];
	rt=merge(merge(A,B),C);
	return an;
}
int qumxsum(int l,int r){//询问[l,r]的最大子列和 
	int A,AA,B,C,an;
	split(rt,A,AA,l-1);
	split(AA,B,C,r-l+1);
	an=mm[B];
	rt=merge(merge(A,B),C);
	return an;
}
int main(){//维修数列 
	int T,n,m,i,x,y,k;char s[19];
	srand(23333);lm[0]=rm[0]=mm[0]=-inf;
	scanf("%d%d",&n,&m);
	for(i=1;i<=n;i++)scanf("%d",&x),rt=merge(rt,newnode(x));
	for(i=0;m--;){
		scanf("%s",s);
		if(s[0]=='I'){
			scanf("%d%d",&x,&k);
			for(i=1;i<=k;i++)scanf("%d",&a[i]);
			for(i=k;i;i--)insert(x,a[i]);
		}
		if(s[0]=='D'){
			scanf("%d%d",&x,&k);
			del(x,x+k-1);
		}
		if(s[0]=='M'&&s[2]=='K'){
			scanf("%d%d%d",&x,&k,&y);
			cov(x,x+k-1,y);
		}
		if(s[0]=='R'){
			scanf("%d%d",&x,&k);
			rev(x,x+k-1);
		}
		if(s[0]=='G'){
			scanf("%d%d",&x,&k);
			printf("%d\n",qusum(x,x+k-1));
		}
		if(s[0]=='M'&&s[2]=='X'){
			printf("%d\n",qumxsum(1,sz[rt]));
		}
	}
}

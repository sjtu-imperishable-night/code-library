#include<bits/stdc++.h>
#define N 500500
#define inf 1e9
using namespace std;
int rt,id,t,q[N*5],a[N],sz[N],F[N],c[N][2],lm[N],rm[N],mm[N],V[N],S[N],cv[N],fcv[N],rv[N];
void REV(int x){
	if(!x)return;
	swap(c[x][0],c[x][1]);
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
	if(fcv[x])COV(c[x][0],cv[x]),COV(c[x][1],cv[x]),fcv[x]=0;
	if(rv[x])REV(c[x][0]),REV(c[x][1]),rv[x]=0;
}
void ps(int x){
	int l=c[x][0],r=c[x][1];
	sz[x]=sz[l]+sz[r]+1;
	S[x]=S[l]+S[r]+V[x];
	lm[x]=max(lm[l],S[l]+V[x]+max(0,lm[r]));
	rm[x]=max(rm[r],S[r]+V[x]+max(0,rm[l]));
	mm[x]=max(max(mm[l],mm[r]),max(0,rm[l])+V[x]+max(0,lm[r]));
}
void R(int x){
	int y=F[x],k=(c[y][0]==x);
	c[y][!k]=c[x][k];F[c[x][k]]=y;
	F[x]=F[y];if(F[y])c[F[y]][c[F[y]][1]==y]=x;
	c[x][k]=y;F[y]=x;ps(y);
}
void sy(int x,int g){
	int y;
	for(pd(x);(y=F[x])!=g;R(x))
		if(F[y]!=g)R((c[y][0]==x)==(c[F[y]][0]==y)?y:x);
	ps(x);if(!g)rt=x;
}
void newnode(int&x,int fa,int z){
	if(t)x=q[t--];else x=++id;
	lm[x]=rm[x]=mm[x]=V[x]=S[x]=z;
	sz[x]=1;F[x]=fa;
	fcv[x]=cv[x]=rv[x]=c[x][0]=c[x][1]=0;
}
void bd(int&k,int l,int r,int fa){//建树 
	if(l>r)return;int md=l+r>>1;
	newnode(k,fa,a[md]);
	if(l<md)bd(c[k][0],l,md-1,k);
	if(r>md)bd(c[k][1],md+1,r,k);
	ps(k);
}
int kth(int x,int z){
	pd(x);
	if(sz[c[x][0]]+1==z)return x;
	return z<=sz[c[x][0]]?kth(c[x][0],z):kth(c[x][1],z-sz[c[x][0]]-1);
}
int get(int l,int r){//得到一段区间 
	int x=kth(rt,l),y=kth(rt,r+2);
	sy(x,0);sy(y,rt);
	return c[c[rt][1]][0];
}
void insert(int x,int z){//在位置x后插入以z为根的子树 
	get(x+1,x);
	F[z]=c[rt][1];c[c[rt][1]][0]=z;
	ps(c[rt][1]);ps(rt);
}
void recycle(int x){
	if(!x)return;
	q[++t]=x;
	recycle(c[x][0]);recycle(c[x][1]);
}
void del(int l,int r){//删除区间[l,r] 
	int x=get(l,r);
	F[x]=0;c[c[rt][1]][0]=0;
	recycle(x);
	ps(c[rt][1]);ps(rt);
}
void cov(int l,int r,int z){//将区间[l,r]赋为z 
	int x=get(l,r);
	COV(x,z);
	ps(c[rt][1]);ps(rt);
}
void rev(int l,int r){//翻转区间[l,r] 
	int x=get(l,r);
	REV(x);
	ps(c[rt][1]);ps(rt);
}
int qusum(int l,int r){//询问[l,r]的和 
	int x=get(l,r);
	return S[x];
}
int qumxsum(int l,int r){//询问[l,r]最大的子列和 
	int x=get(l,r);
	return mm[x];
}
int main(){//维修数列 
	int T,n,m,i,x,y,k;char s[19];
	scanf("%d%d",&n,&m);
	lm[0]=rm[0]=mm[0]=-inf;
	for(i=1;i<=n;i++)scanf("%d",&a[i]);
	bd(rt,0,n+1,0);
	for(i=0;m--;){
		scanf("%s",s);
		if(s[0]=='I'){
			scanf("%d%d",&x,&k);
			for(i=1;i<=k;i++)scanf("%d",&a[i]);
			bd(y,1,k,0);
			insert(x,y);
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
			printf("%d\n",qumxsum(1,sz[rt]-2));
		}
	}	
}

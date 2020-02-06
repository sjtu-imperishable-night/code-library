#include<bits/stdc++.h>//BZOJ3065
#define N 77777
#define M 11111111
using namespace std;
int n,i,x,y,z,o,t1,t2,l,r,mid,now,Q,RT,tp,id,tmp,a[N],dfn[N],ls[N],rs[N],rt[N],st[M],q[N],q1[N],q2[N],L[M],R[M],sz[M];
char s[9];
int nn(){if(tp)return st[tp--];else return ++id;}//回收垃圾分配标号
void rcy(int&k){if(!k)return;st[++tp]=k;rcy(L[k]);rcy(R[k]);sz[k]=0;k=0;}//回收
void ins(int&k,int l,int r,int x,int z){//权值线段树插入
	if(!k)k=nn();if(l==r){sz[k]+=z;return;}int mid=l+r>>1;
	if(x<=mid)ins(L[k],l,mid,x,z);else ins(R[k],mid+1,r,x,z);
	sz[k]=sz[L[k]]+sz[R[k]];if(!sz[k])rcy(k);
}
void bt(int&k,int l,int r){//重建树
	if(l>r)return;int mid=l+r>>1,i;k=dfn[mid];
	if(l==r){ins(rt[k],0,70000,a[k],1);return;}
	for(bt(ls[k],l,mid-1),bt(rs[k],mid+1,r),i=l;i<=r;i++)ins(rt[k],0,70000,a[dfn[i]],1);
}
int mdf(int k,int x,int z){
	ins(rt[k],0,70000,z,1);int t,w=sz[rt[ls[k]]];//往权值线段树中加修改的值
	if(x==w+1)t=a[k],a[k]=z;else if(x<=w)t=mdf(ls[k],x,z);else t=mdf(rs[k],x-w-1,z);
	ins(rt[k],0,70000,t,-1);return t;//删去换掉的值
}
void del(int&k){if(!k)return;rcy(rt[k]);del(ls[k]);q[++o]=k;del(rs[k]);k=0;}//找到重建的点回收
void rbd(int&k){o=0;del(k);for(int i=1;i<=o;i++)dfn[i]=q[i];bt(k,1,o);}//重建
void cha(int&k,int x,int z){
	if(!k){k=++n;ins(rt[k],0,70000,z,1);a[k]=z;return;}
	ins(rt[k],0,70000,z,1);int w=sz[rt[ls[k]]];
	if(x<=w)cha(ls[k],x,z);else cha(rs[k],x-w-1,z);
	if(sz[rt[k]]*0.7>max(sz[rt[ls[k]]],sz[rt[rs[k]]])){//当不平衡时暴力重建
		if(tmp)rbd(tmp==ls[k]?ls[k]:rs[k]),tmp=0;}else tmp=k;
}
void tou(int k,int l,int r){//找出询问区间包含的所有部分
	int L=sz[rt[ls[k]]];
	if(l==1&&r==sz[rt[k]]){q1[++t1]=rt[k];return;}
	if(l<=L+1&&r>=L+1)q2[++t2]=a[k];
	if(r<=L)tou(ls[k],l,r);else if(l>L+1)tou(rs[k],l-L-1,r-L-1);
	else{if(l<=L)tou(ls[k],l,L);if(r>L+1)tou(rs[k],1,r-L-1);}
}
int main(){//用平衡树套权值线段树，不平衡时暴力重建
	for(scanf("%d",&n),i=1;i<=n;i++)scanf("%d",&a[i]),dfn[i]=i;
	for(bt(RT,1,n),scanf("%d",&Q);Q--;){
		scanf("%s%d%d",s,&x,&y);x^=l;y^=l;
		if(s[0]=='Q'){//询问x~y间第k大
			scanf("%d",&z);z^=l;z--;t1=t2=0;tou(RT,x,y);//预处理，降低复杂度
			for(l=0,r=70000;l<r;){//二分
				for(mid=l+r>>1,now=0,i=1;i<=t1;i++)now+=sz[L[q1[i]]];
				for(i=1;i<=t2;i++)if(q2[i]>=l&&q2[i]<=mid)now++;
				if(z<now)for(r=mid,i=1;i<=t1;i++)q1[i]=L[q1[i]];
				else for(l=mid+1,z-=now,i=1;i<=t1;i++)q1[i]=R[q1[i]];
			}
			printf("%d\n",l);
		}
		if(s[0]=='M')mdf(RT,x,y);//修改操作
		if(s[0]=='I'){cha(RT,x-1,y);if(tmp){tmp=0;rbd(RT);}}//插入操作
	}
}

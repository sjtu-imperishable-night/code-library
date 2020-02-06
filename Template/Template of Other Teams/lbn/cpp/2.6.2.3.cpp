#include<bits/stdc++.h>
#define S 777
#define N 50050
using namespace std;
int n,m,i,x,y,l1,l2,L,R,T,sum,las[W],c[N],cnt[N],E[N],v[N],an[N];
char s[9];
struct Q{int l,r,cur,id;}q[N];
struct P{int x,pre,now;}p[N];
bool cmp(Q a,Q b){return E[a.l]<E[b.l]||E[a.l]==E[b.l]&&E[a.r]<E[b.r]||E[a.l]==E[b.l]&&E[a.r]==E[b.r]&&a.cur<b.cur;}
void go(int x){
	if(v[x]){
		if(!--cnt[c[x]])sum--;
	}else{
		if(!cnt[c[x]]++)sum++;
	}
	v[x]^=1;
}
void cg(int x,int y){if(v[x])go(x),c[x]=y,go(x);else c[x]=y;}
int main(){
	scanf("%d%d",&n,&m);
	for(i=1;i<=n;i++)scanf("%d",&c[i]),las[i]=c[i],E[i]=(i-1)/S;
	for(i=1;i<=m;i++){
		scanf("%s%d%d",s,&x,&y);
		if(s[0]=='Q')q[++l1].l=x,q[l1].r=y,q[l1].id=l1,q[l1].cur=l2;
		else p[++l2].x=x,p[l2].pre=las[x],p[l2].now=las[x]=y;
	}
	sort(q+1,q+l1+1,cmp);
	for(L=1,i=1;i<=l1;i++){
		for(;T<=q[i].cur;T++)cg(p[T].x,p[T].now);
		for(;T>q[i].cur;T--)cg(p[T].x,p[T].pre);
		for(;L>q[i].l;go(--L));for(;L<q[i].l;go(L++));
		for(;R>q[i].r;go(R--));for(;R<q[i].r;go(++R));
		an[q[i].id]=sum;
	}
	for(i=1;i<=l1;i++)printf("%d\n",an[i]);
}
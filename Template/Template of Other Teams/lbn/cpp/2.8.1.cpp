#include<bits/stdc++.h>//建树、区间加、区间求和，未验证 
#define N 111111
using namespace std;
int rt,X0,X1,Y0,Y1,O;
struct P{int d[2],mi[2],mx[2],l,r,s,v,lz,sz;}t[N];
bool cmp(P a,P b){return a.d[O]<b.d[O]||a.d[O]==b.d[O]&&a.d[O^1]<b.d[O^1];}
void Max(int&x,int y){x=max(x,y);}
void Min(int&x,int y){x=min(x,y);}
void ADD(int k,int z){
	if(!k)return;
	t[k].v+=z;
	t[k].s+=t[k].sz*z;
	t[k].lz+=z;
}
void pd(int k){
	if(t[k].lz)ADD(t[k].l,t[k].lz),ADD(t[k].r,t[k].lz),t[k].lz=0;
}
int bd(int l,int r,int o){//将[l,r]建树，维度是o 
	O=o;int k=l+r>>1,i;nth_element(t+l+1,t+k+1,t+r+1,cmp);
    for(i=0;i<2;i++)t[k].mi[i]=t[k].mx[i]=t[k].d[i];t[k].lz=t[k].v=t[k].s=0;
    if(l<k)for(O=t[k].l=bd(l,k-1,o^1),i=0;i<2;i++)Min(t[k].mi[i],t[O].mi[i]),Max(t[k].mx[i],t[O].mx[i]);
    if(k<r)for(O=t[k].r=bd(k+1,r,o^1),i=0;i<2;i++)Min(t[k].mi[i],t[O].mi[i]),Max(t[k].mx[i],t[O].mx[i]);
    t[k].sz=t[t[k].l].sz+t[t[k].r].sz+1;return k;
}
void add(int k,int z){//范围+z，范围为[X0,X1][Y0,Y1] 
    if(X0>t[k].mx[0]||X1<t[k].mi[0]||Y0>t[k].mx[1]||Y1<t[k].mi[1])return;
    if(X0<=t[k].mi[0]&&X1>=t[k].mx[0]&&Y0<=t[k].mi[1]&&Y1>=t[k].mx[1]){ADD(k,z);return;}
    if(X0<=t[k].d[0]&&t[k].d[0]<=X1&&Y0<=t[k].d[1]&&t[k].d[1]<=Y1)t[k].v+=z;
    pd(k);add(t[k].l,z);add(t[k].r,z);
	t[k].s=t[k].v+t[t[k].l].s+t[t[k].r].s;
}
int qu(int k){//询问范围和 
	if(X0>t[k].mx[0]||X1<t[k].mi[0]||Y0>t[k].mx[1]||Y1<t[k].mi[1])return 0;
    if(X0<=t[k].mi[0]&&X1>=t[k].mx[0]&&Y0<=t[k].mi[1]&&Y1>=t[k].mx[1])return t[k].s;
    int an=0;
	if(X0<=t[k].d[0]&&t[k].d[0]<=X1&&Y0<=t[k].d[1]&&t[k].d[1]<=Y1)an=t[k].v;
    pd(k);
	return an+qu(t[k].l)+qu(t[k].r);
}
int main(){
	int n,m,lx,z,i;
	scanf("%d%d",&n,&m);
	for(i=1;i<=n;i++)scanf("%d%d",&t[i].d[0],&t[i].d[1]);
	for(rt=bd(1,n,0);m--;){
		scanf("%d%d%d%d%d",&lx,&X0,&Y0,&X1,&Y1);
		if(!lx)scanf("%d",&z),add(rt,z);else printf("%d\n",qu(rt));
	}
}

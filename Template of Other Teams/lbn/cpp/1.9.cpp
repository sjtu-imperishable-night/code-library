#include<bits/stdc++.h>//平面图板子不能有重复点，不能有重复边，边的两点不能相同，都可以用map处理。
#define N 222222
using namespace std;
int n,m,i,j,t,x,y,cnt,to[N],v[N],q[N];
long long Area;
struct P{int x,y;double o;}p[N],e[N];
struct cmp{bool operator()(int a,int b){return e[a].o<e[b].o;}};
long long operator*(P a,P b){return 1ll*a.x*b.y-1ll*a.y*b.x;}
set<int,cmp>S[N];set<int,cmp>::iterator it;
void ADD(int x,int y){printf("%d --- %d\n",x,y);}//在新图中加边
int main(){
	scanf("%d%d",&n,&m);
	for(i=1;i<=n;i++)scanf("%d%d",&p[i].x,&p[i].y);//n个点，若有边权，在e[i].z中记录
	for(i=0;i<m;i++){
		scanf("%d%d",&x,&y);
		e[i<<1]=P{x,y,atan2(p[y].x-p[x].x,p[y].y-p[x].y)};//加双向边，支持双向边权
		e[i<<1|1]=P{y,x,atan2(p[x].x-p[y].x,p[x].y-p[y].y)};
	}
	for(m*=2,i=0;i<m;i++)S[e[i].x].insert(i);
	for(i=0;i<m;i++)if(!v[i]){
		for(q[t=1]=j=i;;q[++t]=j=*it){//按极角排序选最少转动角度找出下一条边
			it=S[e[j].y].upper_bound(j^1);
			if(it==S[e[j].y].end())it=S[e[j].y].begin();
			if(*it==i)break;
		}
		for(Area=0,j=1;j<=t;j++)Area+=p[e[q[j]].x]*p[e[q[j]].y],v[q[j]]=1;
		if(Area>0)for(cnt++,j=1;j<=t;j++)to[q[j]]=cnt;//面积大于0是有限区域
	}
	for(i=0;i<m;i++)ADD(to[i]+1,to[i^1]+1);//若这条边有边权，则在e[i].z中记录
}

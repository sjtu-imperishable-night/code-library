#include<bits/stdc++.h>
#define N 10010
#define CL(a) memset(a,0,sizeof a)
using namespace std;//id[i]为点i的标号，seq[i]为标号为i的点
int n,m,x,y,i,q[N],label[N],id[N],vis[N],seq[N],c[N];
vector<int>G[N];
struct P{
	int lab,u;
	bool operator<(const P&a)const{return lab<a.lab;}
};
void ins(int x,int y){G[x].push_back(y);}
void in(int n){
	for(int i=1;i<=n;i++)G[i].clear();
}
void mcs(){//MCS算法求标号序列
	int i,j,u,v;CL(id);CL(label);CL(seq);
	priority_queue<P>Q;//优先队列做到O(mlgn)，可以拉两个链表做到O(n+m)
	for(i=1;i<=n;i++)Q.push(P{0,i});
	for(i=n;i;i--){
		for(;id[Q.top().u];)Q.pop();
		u=Q.top().u;Q.pop();id[u]=i;
		for(j=0;j<G[u].size();j++){
			v=G[u][j];
			if(!id[v]){
				label[v]++;
				Q.push(P{label[v],v});
			}
		}
	}
	for(i=1;i<=n;i++)seq[id[i]]=i;
}
bool ok(){//判断是否是弦图，期望复杂度O(m)
	int i,j,t,u,v,w;CL(vis);
	for(i=1;i<=n;i++){
		u=seq[i];t=0;//标号从小到大找点
		for(j=0;j<G[u].size();j++){//找标号大于它的点
			v=G[u][j];
			if(id[v]>id[u])q[++t]=v;
		}
		if(!t)continue;
		w=q[1];
		for(j=1;j<=t;j++)if(id[q[j]]<id[w])w=q[j];//找标号大于它的点中最小的
		for(j=0;j<G[w].size();j++)vis[G[w][j]]=i;
		for(j=1;j<=t;j++)//判断是否有连边
			if(q[j]!=w)if(vis[q[j]]!=i)return 0;
	}
	return 1;
}
int setcolor(){//弦图最小染色
	int an=0,i,j,u,v;CL(vis);CL(c);
	for(i=n;i;i--){//按标号序列倒序做
		u=seq[i];
		for(j=0;j<G[u].size();j++)vis[c[G[u][j]]]=i;
		for(j=1;vis[j]==i;j++);//找到最小的没出现的颜色
		c[u]=j;
		an=max(an,j);//更新答案
	}
	return an;
}
int main(){
	scanf("%d%d",&n,&m);in(n);
	for(i=1;i<=m;i++)scanf("%d%d",&x,&y),ins(x,y),ins(y,x);
	mcs();
	puts(ok()?"YES":"NO");
	printf("%d\n",setcolor());
}

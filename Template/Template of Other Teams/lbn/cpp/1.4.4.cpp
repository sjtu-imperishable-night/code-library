#include<bits/stdc++.h>
#define N 505
#define M 250005
#define CL(a) memset(a,0,sizeof a)
using namespace std;
struct blossom{//mat[]匹配点
	int n,m,h,t,W,tot,fir[N],la[M],ne[M],F[N],mat[N],pre[N],tp[N],q[N],vs[N];
	void in(int x,int y){n=x;m=y;W=tot=0;CL(fir);}//初始化
	void ins(int x,int y){la[++tot]=y;ne[tot]=fir[x];fir[x]=tot;}
	void rd(){//读入
		int i,x,y;
		for(i=1;i<=m;i++)scanf("%d%d",&x,&y),ins(x,y),ins(y,x);
	}
	int fd(int x){return F[x]?F[x]=fd(F[x]):x;}
	int lca(int u,int v){
		for(++W;;u=pre[mat[u]],swap(u,v))
			if(vs[u=fd(u)]==W)return u;
			else vs[u]=u?W:0;
	}
	void aug(int u,int v){
		for (int w;u;v=pre[u=w])w=mat[v],mat[mat[u]=v]=u;
	}
	void blo(int u,int v,int f){
		for (int w;fd(u)^f;u=pre[v=w])pre[u]=v,F[u]?0:F[u]=f,F[w=mat[u]]?0:F[w]=f,tp[w]^1?0:tp[q[++t]=w]=-1;
	}
	int bfs(int u){
		int x,E,i;
		for(i=1;i<=n;i++)tp[i]=F[i]=0;
		for(--tp[q[h=t=1]=u];h<=t;u=q[++h])
		for(i=fir[u];i;i=ne[i])if(!tp[E=la[i]]){
			if(!mat[E])return aug(E,u),1;
			pre[E]=u,++tp[E],--tp[q[++t]=mat[E]];
		}else if (tp[E]^1&&fd(u)^fd(E))blo(u,E,x=lca(u,E)),blo(E,u,x);
		return 0;
	}
	int solve(){//返回答案
		int i,an=0;
		for(i=1;i<=n;i++)mat[i]?0:an+=bfs(i);
		return an;
	}
	void out(){//输出每个点的匹配点
		for(int i=1;i<=n;i++)printf("%d%c",mat[i],i==n?'\n':' ');	
	}
}G;
int main(){
	int n,m;
	scanf("%d%d",&n,&m);
	G.in(n,m);
	G.rd();
	printf("%d\n",G.solve());
	G.out();
}

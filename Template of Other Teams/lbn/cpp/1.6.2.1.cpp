#include<bits/stdc++.h>//求割点与割边
#define N 202000
#define M 2002000
using namespace std;
int n,m,i,x,y,tot,id,top,rt,sz,scc,tp,now,st[N],bl[N],cut[N],low[N],dfn[N],fir[N],ans[M],la[M],ne[M];bool ok[M],is[N];
void add(int x,int y){
	for(int i=fir[x];i;i=ne[i])if(la[i]==y){if(i)ok[i]=1;return;}//判重
	la[++tot]=y;ne[tot]=fir[x];ok[tot]=0;fir[x]=tot;
}
void ins(int x,int y){add(x,y);add(y,x);}
int dfs(int x,int fa){
	dfn[x]=low[x]=++id;is[x]=1;st[++tp]=x;
	int i,y,cd=0;
	for(i=fir[x];i;i=ne[i]){
		y=la[i];
		if(!dfn[y]){
			dfs(y,x);cd++;
			if(x!=rt&&dfn[x]<=low[y])cut[++sz]=x;//割点
			low[x]=min(low[x],low[y]);
			if(low[y]>dfn[x]&&!ok[i])ans[++top]=i;//割边
		}else if(y!=fa)low[x]=min(low[x],dfn[y]);
	}
	if(dfn[x]==low[x])for(scc++,now=0;now!=x;)now=st[tp--],is[now]=0,bl[now]=scc;
	return cd;
}
int main(){
	for(scanf("%d%d",&n,&m),tot=1,i=1;i<=m;i++)scanf("%d%d",&x,&y),ins(x,y);
	for(i=1;i<=n;i++)if(!dfn[i]){rt=i;if(dfs(i,0)>1)cut[++sz]=i;}
	for(printf("%d\n",sz),i=1;i<=sz;i++)printf("%d\n",cut[i]);//割点
	for(printf("%d\n",top),i=1;i<=top;i++)printf("%d %d\n",la[ans[i]],la[ans[i]^1]);//割边
	for(puts(""),i=1;i<=n;i++)printf("%d\n",bl[i]);//属于的分量
}

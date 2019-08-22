#include<bits/stdc++.h>//不保证正确，未验证
#define N 222
#define M 44444
#define inf 1e9
#define CL(a) memset(a,0,sizeof a)
using namespace std;
struct ZKW{
	int n,S,T,tot,Flow,Cost,fir[N],ne[M],la[M],va[M],co[M],d[N],slk[N];
	bool v[N];
	void in(){tot=1;CL(fir);}//初始化
	void ins(int x,int y,int fl,int c){
		la[++tot]=y;ne[tot]=fir[x];fir[x]=tot;va[tot]=fl;co[tot]=c;
		la[++tot]=x;ne[tot]=fir[y];fir[y]=tot;va[tot]=0;co[tot]=-c;
	}
	void init(){//读入
		int m,x,y,fl,c,i;
		scanf("%d%d%d%d",&n,&m,&S,&T);
		for(i=1;i<=m;i++)scanf("%d%d%d%d",&x,&y,&fl,&c),ins(x,y,fl,c);
	}
	int modlable(){
		int p=inf,i;
		for(i=1;i<=n;i++){
			if(!v[i]&&slk[i]<p)p=slk[i];
			slk[i]=inf;
		}
		if(p==inf)return 1;
		for(i=1;i<=n;i++)if(v[i])d[i]+=p;
		return 0;
	}
	int dfs(int x,int fl){
		if(x==T){
			Flow+=fl;Cost+=fl*(d[S]-d[T]);
			return fl;
		}
		v[x]=1;
		int left=fl,i,y,p;
		for(i=fir[x];i;i=ne[i])if(va[i]&&!v[y=la[i]]){
			if(d[y]+co[i]==d[x]){
				p=dfs(y,min(left,va[i]));
				va[i]-=p;
				va[i^1]+=p;
				left-=p;
				if(!left){v[x]=0;return fl;}
			}else{
				slk[y]=min(slk[y],d[y]+co[i]-d[x]);
			}
		}
		return fl-left;
	}
	pair<int,int> mincost(){//跑费用流
		int i;
		Flow=0;Cost=0;
		for(i=1;i<=n;i++)d[i]=0;
		do{
			do{
				for(i=1;i<=n;i++)v[i]=0;
			}while(dfs(S,inf));
		}while(!modlable());
		return make_pair(Flow,Cost);
	}
}G;
int main(){
	G.in();
	G.init();
	printf("%d\n",G.mincost().second);	
}

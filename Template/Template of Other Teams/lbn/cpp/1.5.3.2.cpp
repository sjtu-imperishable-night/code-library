#include<bits/stdc++.h>
#define N 222
#define M 222222
#define inf 1e9
#define CL(a) memset(a,0,sizeof a)
int ca,S,T,n,m,i,SS,TT,x,y,B,C;
struct MaxFlow{
	int tot,w,SUM,du[N],fir[N],cur[N],pre[N],d[N],nb[N],va[M],la[M],ne[M],an[M],id[M];
	void in(){tot=1;SUM=0;CL(du);CL(fir);CL(d);CL(nb);CL(pre);}
	void ins(int x,int y,int z,int ID){//每条边的流量和标号
		la[++tot]=y;ne[tot]=fir[x];fir[x]=tot;va[tot]=z;id[tot]=ID;
		la[++tot]=x;ne[tot]=fir[y];fir[y]=tot;va[tot]=0;id[tot]=0;
	}
	void add(int x,int y,int B,int C,int ID){//加入(x,y,B,C) 
		ins(x,y,C-B,ID);
		du[x]-=B;du[y]+=B;//算入流和出流 
		an[ID]=B;
	}
	void prepare(){
		for(int i=1;i<=n;i++){//先和无源汇有上下界可行流一样建图
			if(du[i]>0)ins(SS,i,du[i],0),SUM+=du[i];
			if(du[i]<0)ins(i,TT,-du[i],0);	
		}
		ins(T,S,inf,0);
	}
	int flow(int S,int T,int n){//做从S到T的最大流
		int i,u,V,fl=0;CL(d);CL(nb);
		for(i=1;i<=n;i++)cur[i]=fir[i];
		for(u=S,nb[0]=n;d[S]<n;){
			if(u==T){
				for(V=1e9,i=S;i!=T;i=la[cur[i]])
					if(va[cur[i]]<V)V=va[cur[u=i]];
				for(fl+=V,i=S;i!=T;i=la[cur[i]])
					va[cur[i]]-=V,va[cur[i]^1]+=V;
			}
			for(i=cur[u];i;i=ne[i])
				if(va[i]&&d[la[i]]+1==d[u])break;
			if(i)cur[u]=i,pre[la[i]]=u,u=la[i];else{
				if(!--nb[d[u]])break;
				for(i=cur[u]=fir[u],w=T;i;i=ne[i])
					if(d[la[i]]<w&&va[i])w=d[la[i]];
				++nb[d[u]=w+1];
				if(u!=S)u=pre[u];
			}
		}
		return fl;
	}
	void print(){//输出解
		if(flow(SS,TT,n+2)!=SUM)puts("NO");else{
			fir[SS]=fir[TT]=0;
			printf("%d\n",flow(S,T,n));
			for(i=2;i<=tot;i++)an[id[i]]+=va[i^1];
			for(i=1;i<=m;i++)printf("%d\n",an[i]);		
		}
	}
}G;
int main(){
	G.in();//注意初始化
	scanf("%d%d%d%d",&n,&m,&S,&T);
	SS=n+1;TT=n+2;//新建超级源和超级汇
	for(i=1;i<=m;i++)scanf("%d%d%d%d",&x,&y,&B,&C),G.add(x,y,B,C,i);//读入每条边
	G.prepare();
	G.print();
}

struct CostFlow{//Dijkstra费用流，不保证正确
	int tot,an,fir[N],ne[M],la[M],va[M],co[M],d[N],fa[N],pre[N];
	struct W{int x,z;bool operator<(W a)const{return a.z<z;}};
	void in(){tot=1;an=0;CL(fir);CL(pre);CL(fa);}
	void ins(int x,int y,int fl,int z){
		la[++tot]=y;ne[tot]=fir[x];va[tot]=fl;co[tot]=z;fir[x]=tot;
		la[++tot]=x;ne[tot]=fir[y];va[tot]=0;co[tot]=-z;fir[y]=tot;
	}
	int work(int S,int T,int n){//有负权第一次需要做SPFA，无负权直接做
		int x,y,i,p;
		for(;;){
			priority_queue<W>Q;
			for(i=1;i<=n;i++)d[i]=inf;	
			Q.push(W{S,d[S]=0});
			for(;!Q.empty();){
				W o=Q.top();Q.pop();
				if(d[x=o.x]<o.z)continue;
				for(i=fir[x];i;i=ne[i])
					if(va[i]&&d[x]+co[i]<d[y=la[i]]){
						d[y]=d[x]+co[i];
						pre[y]=i;fa[y]=x;
						Q.push(W{y,d[y]});
					}
			}
			if(d[T]>inf)return an;
			for(p=inf,i=T;i!=S;i=fa[i])p=min(p,va[pre[i]]);
			if(!p)return an;
			for(i=T;i!=S;i=fa[i])va[pre[i]]-=p,va[pre[i]^1]+=p,an+=p*co[pre[i]];
			for(x=1;x<=n;x++)for(i=fir[x];i;i=ne[i])co[i]+=d[x]-d[la[i]];
		}
	}
}G;

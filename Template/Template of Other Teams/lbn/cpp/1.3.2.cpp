template<typename T> struct Dijkstra{
	T d[N];vector<pair<int,T> >V[N];bool v[N];
	void ins(int x,int y,T z){V[x].PB(MP(y,z));}
	void work(int S,int n){//给定起点S和总点数n
		priority_queue<pair<T,int> >Q;int x,y;
		fr(i,n)d[i]=inf,v[i]=0;
		for(Q.push(MP(d[S]=0,S));!Q.empty();v[x]=1)
			if(x=Q.top().Y,Q.pop(),!v[x])
				for(PII o:V[x])if(d[x]+o.Y<d[y=o.X])d[y]=d[x]+o.Y,Q.push(MP(-d[y],y));
	}
};Dijkstra<LL>G;

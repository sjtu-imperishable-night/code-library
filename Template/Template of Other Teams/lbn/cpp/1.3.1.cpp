template<typename T> struct SPFA{
	T d[N];vector<pair<int,T> >V[N];bool v[N];
	void ins(int x,int y,T z){V[x].PB(MP(y,z));}
	void work(int S,int n){//给定起点S和总点数n，方便循环队列
		int x,y;queue<int>Q;Q.push(S);
		fr(i,n)d[i]=inf,v[i]=0;
		for(d[S]=0;!Q.empty();){
			x=Q.front();v[x]=0;Q.pop();
			for(PII o:V[x])if(d[x]+o.Y<d[y=o.X])if(d[y]=d[x]+o.Y,!v[y])v[y]=1,Q.push(y);
		}
	}
};SPFA<LL>G;

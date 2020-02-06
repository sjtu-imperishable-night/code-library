void Prim(){
	memset(v,0,sizeof v);
	int i,j,an=0,u,x;
	for(i=1;i<=N;i++)dis[i]=inf;
	dis[1]=0;
	for(i=1;i<=N;i++){
		u=0;
		for(j=1;j<=n;j++)if(!v[j])if(!u||dis[j]<dis[u])u=j;
		if(!u)break;
		v[u]=1;an+=d[u];
		for(j=0;j<E[u].size();j++)if(!v[x=E[u][j].first])dis[x]=min(dis[x],E[u][j].second);
	}
	return an;
}

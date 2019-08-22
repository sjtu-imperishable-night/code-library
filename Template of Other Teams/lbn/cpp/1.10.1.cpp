void dfs(int x){
	for(int i=1;i<=17;i++)F[x][i]=F[F[x][i-1]][i-1];
	for(int i=fir[x];i;i=ne[i])if(la[i]!=F[x][0]){
		y=la[i];
		F[y][0]=x;
		d[y]=d[x]+1;
		dfs(y);	
	}
}
int lca(int x,int y){
	if(d[x]<d[y])swap(x,y);int t=d[x]-d[y],i;
	for(i=0;i<=17;i++)if(t>>i&1)x=F[x][i];
	for(i=17;i>=0;i--)if(F[x][i]!=F[y][i])x=F[x][i],y=F[y][i];
	return x==y?x:F[x][0];
}

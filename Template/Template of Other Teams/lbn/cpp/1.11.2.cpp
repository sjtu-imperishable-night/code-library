int gettree(int n){//给出n个点间相互距离a[][]，重构树 
	int m,i,x,u,mx;st[m=1]=1;
	for(i=2;i<=n;i++){
		mx=-1;
		fr(j,i-1){
			x=(a[1][i]+a[1][j]-a[j][i])/2;
			if(x>mx)mx=x,u=st[j];
		}
		for(;u>1&&d[F[u]]>=mx;u=F[u]);
		if(d[u]>mx)F[++m]=F[u],d[m]=mx,F[u]=m,u=m;
		if(a[1][i]>mx)F[++m]=u,d[u=m]=a[1][i];
		st[i]=u;
	}
	for(i=2;i<=m;i++)ins(F[i],i,d[i]-d[F[i]]);
	return m;//返回构出树的点数
}

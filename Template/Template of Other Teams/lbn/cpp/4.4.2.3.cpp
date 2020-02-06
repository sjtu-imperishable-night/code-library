void dp(int l,int r,int _l,int _r){
	if(l>r)return;
	int md=l+r>>1,u=_l;
	for(int i=_l;i<=min(_r,md);i++)
		if(g[i-1]+get(i,md)<f[md])f[md]=g[i-1]+get(i,md),u=i;	
	dp(l,md-1,_l,u);dp(md+1,r,u,_r);
}

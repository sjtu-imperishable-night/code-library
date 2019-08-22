void dfs(int x){
	v[x]=1;
	for(int i=fir[x],y;i;i=ne[i])if(d[x]+va[i]<d[y=la[i]]){
		d[y]=d[x]+va[i];
		if(v[y])return 1;
		dfs(y);
	}
	v[x]=0;
}
bool ok(){//返回1找到负环
	memset(d,0,sizeof(d));
	for(int i=1;i<=n;i++)if(dfs(i))return 1;
	return 0;
}

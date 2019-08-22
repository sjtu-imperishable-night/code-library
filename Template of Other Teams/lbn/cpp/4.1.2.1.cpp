int dp(int x){
	//判断终止情况
	if(v[x])return f[x];
	v[x]=1;
	int an=0;
	//更新an，里面的f[y]都用dp(y)
	return f[x]=an;
}

void mknew(int x){//加一个新点
	rk[x]=0;F[x]=x;
}
int fd(int x){//递归路径压缩
	return F[x]==x?x:F[x]=gf(F[x]);
}
int fd(int x){//非递归路径压缩
	int o,w;
	for(o=x;o!=F[o];o=F[o]);
	for(;x!=o;x=w)w=F[x],F[x]=o;
	return o;
}
int fd(int x){//带权并查集
	if(F[x]==x)return x;
	inf o=F[x];
	F[x]=fd(F[x]);
	V[x]+=V[o];
	return F[x];
}
void uni(int x,int y){//普通合并
	F[gf(x)]=gf(y);	
}
void uni(int x,int y){//按秩合并
	x=fd(x);y=fd(y);
	if(x==y)return;
	if(rk[x]<rk[y])F[x]=y;else{
		F[y]=x;
		if(rk[x]==rk[y])rk[x]++;
	}
}

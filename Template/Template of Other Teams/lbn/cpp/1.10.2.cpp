void dfs(int x,int fa){//括号序列，将LCA转变为RMQ
	F[pos[x]=++mt][0]=d[x]=d[fa]+1;
	for(int i=fir[x];i;i=ne[i])if(la[i]!=fa)dfs(la[i],x),F[++mt][0]=d[x];
}
int dis(int x,int y){//RMQ预处理后O(1)询问两点距离
	int w=d[x]+d[y],t;
	x=pos[x];y=pos[y];if(x>y)swap(x,y);t=gl[y-x+1];
	return w-2*min(F[x][t],F[y-(1<<t)+1][t]);
}
int main(){//注意两倍空间
	for(dfs(1,0),i=2;i<=mt;i++)gl[i]=gl[i>>1]+1;
	for(j=1;j<=gl[mt];j++)for(i=1;i+(1<<j)-1<=mt;i++)F[i][j]=min(F[i][j-1],F[i+(1<<j-1)][j-1]);
}

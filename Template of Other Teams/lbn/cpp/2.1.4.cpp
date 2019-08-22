int qu(int x,int y){//RMQ预处理后O(1)询问
	t=gl[y-x+1];
	return max(F[x][t],F[y-(1<<t)+1][t]);
}
for(i=2;i<=n;i++)gl[i]=gl[i>>1]+1;
for(j=1;j<=gl[n];j++)for(i=1;i+(1<<j)-1<=n;i++)F[i][j]=max(F[i][j-1],F[i+(1<<j-1)][j-1]);

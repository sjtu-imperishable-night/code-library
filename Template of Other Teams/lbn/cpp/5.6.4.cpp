for(i=1;i<=n;i++){//模质数意义下高斯消元
	t=Pw(a[i][i],M-2,M);
    for(j=1;j<=n+1;j++)a[i][j]*=t;
	for(j=1;j<=n;j++)if(i!=j)
	for(t=a[j][i],k=1;k<=n+1;k++)
		a[j][k]=(a[j][k]-1ll*t*a[i][k]%M+M)%M;
}

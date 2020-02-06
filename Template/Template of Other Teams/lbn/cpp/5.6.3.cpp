for(i=1;i<=n;i++)b[i][i]=1;//右边是单位矩阵 
	for(i=1;i<=n;i++){
		for(t=a[i][i],j=1;j<=n;j++)
			a[i][j]/=t,b[i][j]/=t;//处理主元行 
		for(j=1;j<=n;j++)
			if(i!=j)for(t=a[j][i],k=1;k<=n;k++)
  				a[j][k]-=t*a[i][k],b[j][k]-=t*b[i][k];
	}

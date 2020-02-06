for(k=1;k<=n;k++)
	for(i=1;i<=n;i++)if(i!=k)
		for(j=1;j<=n;j++)if(i!=j&&k!=j)
			if(d[i][k]+d[k][j]<d[i][j])d[i][j]=d[i][k]+d[k][j];

for(i=1;i<=n;i++){//对n行n+1列的矩阵的第i行进行消元
	t=a[i][i];//先记录t=a(i,i)，避免出错????
	for(j=1;j<=n+1;j++)a[i][j]/=t;//将主元行均除以a(i,i)，使a(i,i)变为1
	for(j=1;j<=n;j++)
		if(i!=j)//对非主元行进行操作
			for(t=a[j][i],k=1;k<=n+1;k++)//先记录t=a(j,i)
 				a[j][k]-=t*a[i][k];//a(j,k)-=a(j,i)*a(i,k)
}

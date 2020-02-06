for(i=1;i<=n;i++)
	for(j=a[i];j<=V;j++)
		f[j]=max(f[j],f[j-a[i]]+b[i]);
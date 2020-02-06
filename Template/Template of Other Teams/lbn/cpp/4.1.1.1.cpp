for(i=1;i<=n;i++)
	for(j=V;j>=a[i];j--)
		f[j]=max(f[j],f[j-a[i]]+b[i]);

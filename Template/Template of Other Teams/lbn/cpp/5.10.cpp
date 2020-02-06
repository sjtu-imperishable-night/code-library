	scanf("%d",&n);
	for(i=1;i<=n;i++)scanf("%d",&a[i]);
	for(i=1;i<=n;i++)if(!v[i]){
		for(v[p=i]=sz=1;!v[a[p]];v[p=a[p]]=1)sz++;
	}

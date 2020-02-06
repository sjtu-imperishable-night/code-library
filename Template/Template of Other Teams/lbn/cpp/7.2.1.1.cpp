	for(i=1;i<=n;i++)scanf("%d",&a[i]),v[i]=x[i];
	sort(v+1,v+n+1);cnt=unique(v+1,v+n+1)-v-1;
	for(i=1;i<=n;i++)a[i]=lower_bound(v+1,v+cnt+1,a[i])-v;

	scanf("%d%d",&n,&k);
	for(i=1;i<=n;i++)scanf("%d",&a[i]);
	nth_element(a+1,a+k,a+n+1);
	printf("%d\n",a[k]);

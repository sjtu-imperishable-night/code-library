for(i=1;i<=n;i++){
	for(;h<=t&&a[i]>=q[t];t--);
	for(q[++t]=i;h<=t&&i-q[h]>w;h++);
	an[i]=a[q[h]];
}
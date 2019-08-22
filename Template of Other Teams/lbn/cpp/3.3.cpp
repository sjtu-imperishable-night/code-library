for(;m--;){
	for(scanf("%s",s),u=i=0;i<n;u=c[u][o],i++)
	if(!c[u][o=s[i]-'a'])c[u][o]=++id;
	V[u]++;
}

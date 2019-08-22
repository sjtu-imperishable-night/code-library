//倒序建立后缀自动机
for(v[S]=i=1;i<=cnt;i++)if(to[i]&&!v[i])
	for(p=n,j=i;!v[j];v[j]=1,j=F[j],p--){
		p-=st[j]-st[F[j]]-1;
		ch[F[j]][s[p]-'a']=j;//类似字典树存后缀树的边
		len[F[j]][s[p]-'a']=st[j]-st[F[j]];
		ins(F[j],j,st[j]-st[F[j]]);//邻接表存边
	}

	for(i=1;i<=m;i++){
		scanf("%d%d",&x,&y);if(dfn[x]>dfn[y])swap(x,y);
		t=lca(x,y);if(t==x)q[i].l=l[x];else q[i].l=r[x];//判断每个询问在括号序列中对应位置
		q[i].r=l[y];q[i].id=i;
	}
	sort(q+1,q+m+1,cmp);L=1;R=0;
	for(i=1;i<=m;i++){
		for(;L>q[i].l;go(to[--L]));
		for(;L<q[i].l;go(to[L++]));
		for(;R>q[i].r;go(to[R--]));
		for(;R<q[i].r;go(to[++R]));
		x=to[L];y=to[R];t=lca(x,y);
		if(x!=t&&y!=t)go(t);//LCA特判更新，因为会走两遍抵消
		ans[q[i].id]=now;
		if(x!=t&&y!=t)go(t);
	}

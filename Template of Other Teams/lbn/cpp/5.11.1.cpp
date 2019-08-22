	memset(a,0,sizeof a);a[0]=1;//初始化 
	for(i=1;i<=n;i++){//乘上每个物品对应的母函数 
		memset(b,0,sizeof b);//清空 
		for(j=l[i];j<=r[i]&&j*w[i]<=M;j++)//枚举母函数每一项 
			for(k=0;k+j*w[i]<=M;k++)//枚举当前物品重量每一项 
				b[k+j*w[i]]+=a[k];//暴力卷积计算 
		memcpy(a,b,sizeof b);//循环赋值 
	}

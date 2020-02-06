	scanf("%d%d",&n,&r);//n为物品数,r为选出的个数
	memset(a,0,sizeof a);a[0]=1.0;//注意类型为实数
	for(i=1;i<=n;i++){
		memset(b,0,sizeof b);//清空
		scanf("%d",&x);//个数
		for(j=0;j<=r;j++)//枚举指数型母函数每一项 
			for(k=0;k<=x&&k+j<=r;k++)//枚举当前物品重量每一项 
			b[k+j]+=a[j]/pw[k];//暴力卷积计算
			memcpy(a,b,sizeof b);//循环赋值
		}
	printf("%.0lf\n",a[r]*pw[r]);

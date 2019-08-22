bool ok(LL g,LL p){//验证g是否是模p的原根，外部调用快速幂
	for(int i=1;i<=t;i++)//如果g^((p-1)/qi) mod p=1，那么g不是模p的原根
		if(Pw(g,(p-1)/q[i],p)==1)return 0;
	return 1;
}
LL primitive_root(LL p){//求原根
	LL i,n=p-1,g=1;t=0;
	for(i=2;i*i<=n;i++)//分解质因数
        if(n%i==0)for(q[++t]=i;n%i==0;n/=i);
	if(n!=1)q[++t]=n;
	for(;;g++)//暴力枚举判断
		if(ok(g,p))return g;
}

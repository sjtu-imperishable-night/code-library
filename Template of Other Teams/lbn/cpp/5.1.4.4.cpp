LL inv(LL i,LL m){//递归求单个数的逆元
	if(i==1)return 1;
	return inv(m%i)*(m-m/i)%m;
}
for(inv[1]=1,i=2;i<=n;i++)//线性递推逆元
	inv[i]=inv[M%i]*(M-M/i)%M;

void Sqrt(int*A,int*B,int n){//将多项式A开根，结果在B中，n为2的幂次
	static int D[N],IB[N];
	B[0]=1;B[1]=0;//n=1时根据题意或二次剩余求解
	int I2=Pw(2,M-2,M),m,i;
	for(m=2;m<=n;m<<=1){//递归转递推
		for(i=0;i<m;i++)D[i]=A[i];
		for(i=m;i<2*m;i++)D[i]=B[i]=0;
		NTT(D,m*2);Inv(B,IB,m);NTT(IB,m*2);NTT(B,m*2);
		for(i=0;i<m*2;i++)B[i]=(1ll*B[i]*I2+1ll*I2*D[i]%M*IB[i])%M;
		NTT(B,m*2,-1);for(i=m;i<m*2;i++)B[i]=0;
	}
}

void Inv(int*A,int*B,int n){//求B=A^{-1}，n为2的幂次
	static int C[N];
	B[0]=Pw(A[0],M-2,M);B[1]=0;//n=1时B[0]=A[0]^-1
	for(int m=2,i;m<=n;m<<=1){//递归转递推
		for(i=0;i<m;i++)C[i]=A[i];
		for(i=m;i<2*m;i++)C[i]=B[i]=0;//在模x^m意义下，超过m次均为0
		NTT(C,m*2);NTT(B,m*2);//g(x)≡g_0(x)(2-f(x)g_0(x))(mod x^n)
		for(i=0;i<m*2;i++)B[i]=1ll*B[i]*(2-1ll*B[i]*C[i]%M+M)%M;
		NTT(B,m*2,-1);
		for(i=m;i<m*2;i++)B[i]=0;//在模x^m意义下，超过mn次均为0
	}
}

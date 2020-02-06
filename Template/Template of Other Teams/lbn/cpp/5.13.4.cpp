void Div(int *A,int *B,int *D,int *R,int n,int m){//给定n次多项式A(x)和m次多项式B(x)，求D(x)和R(x)使A(x)=B(x)D(x)+R(x)
	static int A0[N],B0[N];
	int p=1,t=n-m+1;
	for(;p<t<<1;)p<<=1;
	fill(A0,A0+p,0);reverse_copy(B,B+m,A0);
	Inv(A0,B0,t);//t不是2的幂次
	fill(B0+t,B0+p,0);NTT(B0,p);
	reverse_copy(A,A+n,A0);
	fill(A0+t,A0+p,0);NTT(A0,p);
	for(int i=0;i<p;++i)A0[i]=1ll*A0[i]*B0[i]%M;
	NTT(A0,p,-1);reverse(A0,A0+t);copy(A0,A0+t,D);
	for(p=1;p<n;p<<=1);
	fill(A0+t,A0+p,0);NTT(A0,p);
	copy(B,B+m,B0);fill(B0+m,B0+p,0);NTT(B0,p);
	for(int i=0;i!=p;++i)A0[i]=1ll*A0[i]*B0[i]%mod_v;
	NTT(A0,p,-1);
	for(int i=0;i<m;++i)R[i]=(A[i]-A0[i]+M)%M;
	fill(R+m,R+p,0);
}

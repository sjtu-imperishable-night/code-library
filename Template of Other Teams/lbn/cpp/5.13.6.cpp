void Ln(int n,CP *A,CP *B){
	static CP A0[N*4],A1[N*4];
	int N=1;for(;N<n<<1;)N<<=1;
	for(int i=0;i<N;i++)A0[i]=A1[i]=0.0;
	Inv(n,A,A0);
	for(int i=0;i<n-2;i++)A1[i]=A[i+1]*double(i+1);A1[n-1]=0.0;
	FFT(N,A0,1);FFT(N,A1,1);
	for(int i=0;i<N;i++)A0[i]*=A1[i];
	FFT(N,A0,-1);
	for(int i=0;i<n-2;i++)B[i+1]=A0[i]/double(i+1);B[0]=0.0;
	for(int i=n;i<N;i++)B[i]=0.0;
}

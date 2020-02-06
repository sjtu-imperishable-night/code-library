#define N 555
struct JZ{
	int n,m,a[N][N];
	void cl(){n=m=0;memset(a,0,sizeof a);}
	JZ operator+(JZ b)const{
		JZ c;c.n=n;c.m=m;
		for(int i=0;i<n;i++)
			for(int j=0;j<m;j++)
				c.a[i][j]=a[i][j]+b.a[i][j];
		return c;
	}
	JZ operator-(JZ b)const{
		JZ c;c.n=n;c.m=m;
		for(int i=0;i<n;i++)
			for(int j=0;j<m;j++)
				c.a[i][j]=a[i][j]-b.a[i][j];
	}
	JZ operator*(JZ b)const{
		JZ c;c.cl();c.n=n;c.m=b.m;
		for(int i=0;i<n;i++)
			for(int j=0;j<b.m;j++)
				for(int k=0;k<m;k++)
					c.a[i][j]+=a[i][k]*b.a[k][j];
		return c;
	}
};

#include<bits/stdc++.h>
using namespace std;

long long C[5050][5050];

long long _4[5050];

long long f[5050],g[5050];

int main()
{
	int N,M;
	scanf("%d%d",&N,&M);
	
	for(int i=0;i<=N;i++)
	{
		C[i][0]=1;
		for(int j=1;j<=i;j++)
		{
			C[i][j]=C[i-1][j-1]+C[i-1][j];
			if(C[i][j]>=M)
				C[i][j]-=M;
		}
	}
	
	for(int i=2;i<=N;i+=2)
	{
		for(int j=0;j<=i/2;j++)
		{
			f[i]+=C[i][j]*C[i-j][j]%M*C[i-j-j][i/2-j]%M;
			if(f[i]>=M)
				f[i]-=M;
		}
	}
	
	for(int i=2;i<=N;i+=2)
	{
		g[i]=f[i];
		for(int j=2;j<i;j+=2)
		{
			g[i]-=f[i-j]*g[j]%M;
			if(g[i]<0)
				g[i]+=M;
		}
	}
	
	_4[0]=1;
	for(int i=1;i<=N;i++)
		_4[i]=_4[i-1]*4%M;
	
	long long ans=_4[N]*(N+1)%M;
	
	for(int i=2;i<=N;i+=2)
	{
		ans-=(N-i+1)*g[i]%M*_4[N-i]%M;
		if(ans<0)
			ans+=M;
	}
	printf("%lld\n",ans);
	return 0;
}

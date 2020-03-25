#include<bits/stdc++.h>
using namespace std;

const int mod=1e9+7;

int a[2020],b[2020];

int f[2020];
int dp[2020][2020];

int main()
{
	int N;
	scanf("%d",&N);
	
	for(int i=1;i<=N;i++)
		scanf("%d",&a[i]);
	for(int i=1;i<=N;i++)
		scanf("%d",&b[i]);
	
	f[1]=1;
	for(int i=2;i<=N;i++)
	{
		for(int j=1;j<i;j++)
		{
			f[i]+=1ll*f[j]*f[i-j]%mod;
			if(f[i]>=mod)
				f[i]-=mod;
		}
	}
	for(int i=0;i<=N;i++)
		dp[0][i]=dp[i][0]=1;
	
	for(int i=1;i<=N;i++)
	for(int j=1;j<=N;j++)
	{
		dp[i][j]=dp[i-1][j]+dp[i][j-1];
		if(dp[i][j]>=mod)
			dp[i][j]-=mod;
		for(int k=1;k<=min(i,j)&&a[i-k+1]==b[j-k+1];k++)
		{
			dp[i][j]-=1ll*f[k]*dp[i-k][j-k]%mod;
			if(dp[i][j]<0)
				dp[i][j]+=mod;
		}
	}
	printf("%d\n",dp[N][N]);
	return 0;
}

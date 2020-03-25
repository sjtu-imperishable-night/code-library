#include<bits/stdc++.h>
using namespace std;

int dp[51][1010][1010];
int s[51][1010][1010];
int a[1010];

int main()
{
	int N,K;
	scanf("%d%d",&N,&K);
	for(int i=1;i<=N;i++)
		scanf("%d",&a[i]);
	sort(a+1,a+N+1);
	for(int i=0;i<=K;i++)
	{
		for(int k=1;k<=N;k++)
			for(int j=k;j>=1;j--)
			{
				dp[i][j][k]=1e9;
				if(j==k)
				{
					dp[i][j][k]=0;
					s[i][j][k]=j;
				}
				else if(i>0)
				{
					for(int l=max(s[i][j][k-1],j);l<=s[i][j+1][k]&&l<k;l++)
					if(dp[i][j][k]>dp[i-1][j][l]+dp[i-1][l+1][k]+a[k]-a[l])
					{
						dp[i][j][k]=dp[i-1][j][l]+dp[i-1][l+1][k]+a[k]-a[l];
						s[i][j][k]=l;
					}
					dp[i][j][k]=min(dp[i][j][k],dp[i-1][j][k]);
				}
			}
	}
	printf("%d\n",dp[K][1][N]);
	return 0;
}

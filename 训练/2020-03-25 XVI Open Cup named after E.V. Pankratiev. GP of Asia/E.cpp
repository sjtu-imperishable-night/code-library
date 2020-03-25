#include<bits/stdc++.h>
using namespace std;

int a[1010],dp[1010]; 

int main()
{
	int N;
	scanf("%d",&N);
	for(int i=1;i<=N;i++)
		scanf("%d",&a[i]);
	sort(a+1,a+N+1);
	for(int i=1;i<=N;i++)
		dp[i]=2020202020;
	for(int i=1;i<=N;i++)
	{
		for(int j=i-1;j>=0;j--)
		if(a[i]>dp[j])
			dp[j+1]=min(dp[j+1],dp[j]+a[i]);
	}
	for(int i=N;i>=0;i--)
	if(dp[i]<2020202020)
	{
		printf("%d\n",i);
		return 0;
	}
	return 0;
}

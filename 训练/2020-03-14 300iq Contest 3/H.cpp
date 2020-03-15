#include<bits/stdc++.h>
using namespace std;

const int mod = 998244353;

int a[5050],f[5050];

int main()
{
	int n;
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%d",&a[i]);
	
	sort(a+1,a+n+1);	
	
	f[0]=1;
	int ans=0;
	int last=0;
	for(int i=1;i<=n;i++)
	{
		while(last<a[i])
		{
			for(int j=n;j>=1;j--)
			{
				f[j]+=f[j-1];
				if(f[j]>=mod)
					f[j]-=mod;
			}
			last++;
		}
		ans+=f[1];
		if(ans>=mod)
			ans-=mod;
		for(int j=2;j<=n;j++)
		{
			f[j-1]+=1ll*f[j]*j%mod*(j-1)%mod;
			if(f[j-1]>=mod)
				f[j-1]-=mod;
		}
	}
	for(int i=1;i<=n;i++)
	{
		ans-=a[i];
		if(ans<0)
			ans+=mod;
	}
	ans=1ll*ans*(mod+1)/2%mod;
	printf("%d\n",ans);
	return 0;
}

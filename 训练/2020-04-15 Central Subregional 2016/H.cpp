#include<bits/stdc++.h>
using namespace std;
int main()
{
	int n;
	scanf("%d",&n);
	long long ans=1;
	for(int i=1;i<=min(9,n);i++)
		if(i==1)
			ans*=8;
		else
			ans*=9;
	printf("%lld",ans);
	for(int i=10;i<=n;i++)
		printf("0");
	puts("");
	return 0;
}

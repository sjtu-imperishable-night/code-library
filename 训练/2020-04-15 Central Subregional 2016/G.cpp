#include<bits/stdc++.h>
using namespace std;
int main()
{
	int n;
	scanf("%d",&n);
	int cnt=0;
	for(int i=2;i*i<=n;i++)
	{
		if(n%i==0)
		{
			n/=i;
			if(n%i==0)
			{
				puts("NO");
				return 0;
			}
			cnt++;
		}
	}
	if(cnt==2&&n>1)
	{
		puts("YES");
		return 0;
	}
	if(cnt==3&&n==1)
	{
		puts("YES");
		return 0;
	}
	puts("NO");
	return 0;
}

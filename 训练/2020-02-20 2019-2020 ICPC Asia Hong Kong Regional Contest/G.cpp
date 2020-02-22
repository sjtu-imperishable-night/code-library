#include<bits/stdc++.h>
using namespace std;
int main()
{
	int K;
	scanf("%d",&K);
	if(K==1)
	{
		puts("2");
		puts("1");
		puts("1 2");
		return 0;
	}
	if(K<=10000)
	{
		printf("%d\n",K);
		for(int i=1;i<K;i++)
			printf("%d ",i);
		puts("");
		for(int i=1;i<=K;i++)
			printf("%d ",1);
		return 0;
	}
	
	for(int j=sqrt(K);j>=1;j--)
	{
		int n=j,m=K/n,p=K-n*m;
		if(n+m+p+1<=100000)
		{
			printf("%d\n",n+m+p+1);
			for(int i=1;i<=p+n;i++)
				printf("%d ",i);
			printf("%d ",p+1);
			for(int i=2;i<=m;i++)
				printf("%d ",p+n+i);
			puts(" ");
			printf("%d ",100);
			for(int i=1;i<=p;i++)
				printf("%d ",2);
			for(int i=1;i<=n+m;i++)
				printf("%d ",1);
			return 0;
		}
	}
	return 0;
}

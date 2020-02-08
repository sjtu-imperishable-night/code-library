#include<bits/stdc++.h>
using namespace std;
int a[101010],b[101010];

int n,k;
bool check()
{
	bool flag=0;
	for(int i=1;i<k;i++)
	if(a[i]<a[i+1])
	{
		flag=1;
		break;
	}
	for(int i=k+1;i<=n;i++)
	if(a[i]>a[k])
	{
		flag=1;
		break;
	}
	if(flag==0)
		return 1;
	return 0;
}

int main()
{
	scanf("%d%d",&n,&k);
	for(int i=1;i<=n;i++)
		scanf("%d",&a[i]);
	
	if(n==k)
	{
		puts("1");
		return 0;
	}
	
	int max_num=0;
	for(int i=1;i<=n;i++)
		max_num=max(max_num,a[i]);
	
	for(int i=1;i<=n;i++)
	{
		if(a[i]==max_num)
			b[i]=b[i-1]+1;
		else
			b[i]=0;
		if(b[i]==k)
		{
			printf("%d\n",i-k+1);
			return 0;
		}
	}
	
	if(check())
	{
		puts("1");
		return 0;
	}
	reverse(a+1,a+n+1);
	if(check())
	{
		printf("%d\n",n-k+1);
		return 0;
	}
	puts("-1"); 
	return 0;
}

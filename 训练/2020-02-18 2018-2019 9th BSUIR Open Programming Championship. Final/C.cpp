#include<bits/stdc++.h>
using namespace std;
int n,m;

int pos(int x,int y)
{
	return x*m+y; 
}

int a[1010101],b[1010101];

char S[1010101]; 

int check(int step)
{
	for(int i=0;i<n;i++)
	for(int j=0;j<m;j++)
	{
		b[pos(i,j)]=a[pos(i,j)];
		if(i>=step)
			b[pos(i,j)]^=b[pos(i-step,j)];
		if(j>=step)
			b[pos(i,j)]^=b[pos(i,j-step)];
		if(i>=step&&j>=step)
			b[pos(i,j)]^=b[pos(i-step,j-step)];
		if(b[pos(i,j)]!=a[pos(i,j)])
			return 0;
	}
	return 1;
}

int main()
{
	scanf("%d%d",&n,&m);
	
	for(int i=0;i<n;i++)
	{
		scanf("%s",S); 
		for(int j=0;j<m;j++)
			a[pos(i,j)]=S[j]-'0';
	}
	long long step=1; 
	while(1)
	{
		if(check(step))
		{
			printf("%lld\n",step);
			return 0;
		}
		step*=2;
	}
	return 0;
}

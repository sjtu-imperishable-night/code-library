#include<bits/stdc++.h>
using namespace std;

int N;

int a[1010101];

int n,k;

bool check(int x)
{
	int last=n;
	for(int i=1;i<N;i++)
		if(a[i+1]-a[i]<=x&&last>0)
		{
			if(N-i+1<2*last*k)
				return 0;
			i++;
			last--;
		}
	if(last>0)
		return 0;
	return 1;
}

int main()
{
	scanf("%d%d",&n,&k);
	N=2*n*k;
	for(int i=1;i<=N;i++)
		scanf("%d",&a[i]);
	sort(a+1,a+N+1);
	int l=0,r=1e9;
	while(l<r)
	{
		int m=(l+r)/2;
		if(check(m))
			r=m;
		else
			l=m+1;
	}
	printf("%d\n",l);
	return 0;
}

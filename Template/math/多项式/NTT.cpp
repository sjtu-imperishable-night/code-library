#include<bits/stdc++.h>
using namespace std;
const int mod=1004535809;
int Pow(int a,int b)
{
	int ret=1;
	while(b)
	{
		if(b&1)
			ret=1ll*ret*a%mod;
		a=1ll*a*a%mod;
		b/=2;
	}
	return ret;
}

const int MAXN=(1<<18)+10;

struct NumberTheoreticTransform{
	int n,rev[MAXN];
	int g;
	void ini(int lim)
	{
		g=3;
		n=1;
		int k=0;
		while(n<=lim)
		{
			n<<=1;
			k++;
		}
		for(int i=0;i<n;i++)
			rev[i]=(rev[i>>1]>>1)|((i&1)<<(k-1));
	}
	void dft(int *a,int flag)
	{
		for(int i=0;i<n;i++)
		if(i<rev[i])
			swap(a[i],a[rev[i]]);
		for(int l=2;l<=n;l<<=1)
		{
			int m=l>>1;
			int wn=Pow(g,flag==1?((mod-1)/l):(mod-1-(mod-1)/l));
			for(int *p=a;p!=a+n;p+=l)
			{
				int w=1;
				for(int k=0;k<m;k++)
				{
					int t=1ll*w*p[k+m]%mod;
					p[k+m]=(p[k]-t+mod)%mod;
					p[k]=(p[k]+t)%mod;
					w=1ll*w*wn%mod;
				}
			}
		}
		if(flag==-1)
		{
			long long inv=Pow(n,mod-2);
			for(int i=0;i<n;i++)
				a[i]=1ll*a[i]*inv%mod;
		}
	}
	void mul(int *a,int *b,int m)
	{
		ini(m);
		dft(a,1);
		dft(b,1);
		for(int i=0;i<n;i++)
			a[i]=1ll*a[i]*b[i]%mod;
		dft(a,-1);
	}
}f;
int a[404040],b[404040];
int main()
{
	int n1,n2;
	scanf("%d%d",&n1,&n2);
	for(int i=0;i<=n1;i++)
		scanf("%d",&a[i]);
	for(int i=0;i<=n2;i++)
		scanf("%d",&b[i]);
	int m=n1+n2;
	f.mul(a,b,m);
	for(int i=0;i<=m;i++)
		printf("%d ",a[i]);
	printf("\n");
	return 0;
}

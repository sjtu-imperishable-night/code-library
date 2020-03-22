#include<bits/stdc++.h>
using namespace std;

const int magic1 = 131, magic2 = 2333, magic3 = 13, magic4 = 23, magic5 = 10007;

unsigned long long hsh[111],tmp[111],buf[111][111],_magic2[111];
vector<int> G[111];
map<unsigned long long,int> m;
set<int> s[111];

unsigned long long qpow(unsigned long long n,int k)
{
	unsigned long long ret=1;
	while(k)
	{
		if(k&1)
			ret*=n;
		n*=n;
		k/=2;
	}
	return ret;
}

int main()
{
	int n;
	scanf("%d",&n);
	
	for(int i=1;i<=n;i++)
	{
		int k;
		scanf("%d",&k);
		hsh[i]=k;
		for(int j=1;j<=k;j++)
		{
			int x;
			scanf("%d",&x);
			G[i].push_back(x);
		}
	}
	_magic2[0]=1;
	for(int i=1;i<=n;i++)
		_magic2[i]=_magic2[i-1]*magic2;
	
	int round = 1000;
	while(round--)
	{
		memset(tmp,0,sizeof(tmp));
		memset(buf,0,sizeof(buf));
		
		for(int i=1;i<=n;i++)
		{
			for(int j=0;j<int(2*G[i].size());j++)
			{
				int jj=j%int(G[i].size());
				if(j>0)
					buf[i][G[i][jj]]=buf[i][G[i][(j-1)%int(G[i].size())]];
				buf[i][G[i][jj]]*=magic2;
				buf[i][G[i][jj]]+=hsh[G[i][jj]];
				if(j>=int(G[i].size()))
					buf[i][G[i][jj]]-=hsh[G[i][jj]]*_magic2[G[i].size()];
			}
		}
		
		for(int i=1;i<=n;i++)
		{
			unsigned long long p = 1;
			for(int x:G[i])
			{
				p*=hsh[x]+buf[x][i]+magic1;
				tmp[i]+=buf[x][i]*buf[x][i]*buf[x][i];
				tmp[i]+=hsh[x];
				tmp[i]+=hsh[x]*hsh[x]*hsh[x];
				tmp[i]+=buf[x][i];
			}
			tmp[i]+=magic5;
			tmp[i]+=G[i].size();
			tmp[i]+=p;
		}
		for(int i=1;i<=n;i++)
			hsh[i]=tmp[i];
	}
	
	for(int i=1;i<=n;i++)
	{
		//cout<<hsh[i]<<" ";
		if(m[hsh[i]]==0)
			m[hsh[i]]=i;
		s[m[hsh[i]]].insert(i);
	}
	bool flag=0;
	for(int i=1;i<=n;i++)
	{
		if(s[i].size()>1)
		{
			flag=1;
			for(int x:s[i])
				printf("%d ",x);
			puts("");
		}
	}
	if(!flag)
	{
		puts("none");
	}
	return 0;
}

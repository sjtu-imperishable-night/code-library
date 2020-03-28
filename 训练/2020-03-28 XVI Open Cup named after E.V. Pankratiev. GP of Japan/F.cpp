#include<bits/stdc++.h>
using namespace std;

int f[1010][202];

vector<int> G[202],D[202],V[202];

int main()
{
	int N,M,P;
	scanf("%d%d%d",&N,&M,&P);
	
	for(int i=1;i<=M;i++)
	{
		int s,t,d,v;
		scanf("%d%d%d%d",&s,&t,&d,&v);
		G[s].push_back(t);
		G[t].push_back(s);
		D[s].push_back(d);
		D[t].push_back(d);
		V[s].push_back(v);
		V[t].push_back(v);
	}
	
	for(int i=0;i<=P;i++)
	{
		for(int j=1;j<=N;j++)
			f[i][j]=-1e9;
	}
	
	f[0][1]=0;
	
	double ans=0;
	
	for(int i=0;i<=P;i++)
	{
		for(int j=1;j<=N;j++)
		if(f[i][j]>=0)
		{
			for(int k=0;k<G[j].size();k++)
			{
				if(i+2*D[j][k]<=P)
					f[i+2*D[j][k]][G[j][k]]=max(f[i+2*D[j][k]][G[j][k]],f[i][j]+2*V[j][k]);
				ans=max(ans,f[i][j]+1.0*(P-i)*V[j][k]/D[j][k]);
			}
		}
	}
	printf("%.10f\n",ans);
	return 0;
}

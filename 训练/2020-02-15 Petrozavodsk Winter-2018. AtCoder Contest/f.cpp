#include<bits/stdc++.h>
using namespace std;

vector<int> G[202020];
int d[202020];

int fucked[202020];

void dfs(int u,int fa)
{
	if(d[u]>2)
	{
		fucked[u]=1;
		return;
	}
	for(int v:G[u])
	{
		if(v!=fa)
			dfs(v,u);
	}
}

int main()
{
	int n;
	scanf("%d",&n);
	for(int i=1;i<n;i++)
	{
		int u,v;
		scanf("%d%d",&u,&v);
		d[u]++;
		d[v]++;
		G[u].push_back(v);
		G[v].push_back(u);
	}
	int cnt=0;
	for(int i=0;i<n;i++)
		if(d[i]==1)
			cnt++;
	if(cnt==2)
	{
		puts("1");
		return 0;
	}
	
	for(int i=0;i<n;i++)
	if(d[i]==1)
		dfs(i,-1);
	
	for(int i=0;i<n;i++)
		if(fucked[i]==1)
			cnt--;
	printf("%d\n",cnt); 
	return 0;
}

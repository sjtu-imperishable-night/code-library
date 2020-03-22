#include<bits/stdc++.h>
using namespace std;
int vis[1010];

vector<int> p[10101];

int ma[10101],t[10101];

int main()
{
	freopen("generators.in","r",stdin);
	freopen("generators.out","w",stdout);
	int N,K;
	scanf("%d%d",&N,&K);
	long long _ans=0;
	for(int i=1;i<=N;i++)
	{
		int a,b,c,x;
		scanf("%d%d%d%d",&x,&a,&b,&c);
		memset(vis,0,sizeof(vis));
		ma[i]=0;
		int now=0;
		while(vis[x]==0)
		{
			if(x>ma[i])
			{
				ma[i]=x;
				t[i]=now;
			}
			p[i].push_back(x);
			vis[x]=1;
			x=(a*x+b)%c;
			now++;
		}
		_ans+=ma[i];
	}
	if(_ans%K==0)
	{
		long long ans=-1;
		int cg1=0,cg2=0;
		for(int i=1;i<=N;i++)
		{
			for(int j=0;j<p[i].size();j++)
				if((ma[i]-p[i][j])%K!=0)
				{
					if(ans<_ans-ma[i]+p[i][j])
					{
						ans=_ans-ma[i]+p[i][j];
						cg1=i;
						cg2=j;
					}
				}
		}
		if(ans>=0)
		{
			t[cg1]=cg2;
			printf("%lld\n",ans);
			for(int i=1;i<=N;i++)
				printf("%d ",t[i]);
			puts("");
		}
		else
			puts("-1");
		return 0;
	}
	printf("%lld\n",_ans);
	for(int i=1;i<=N;i++)
		printf("%d ",t[i]);
	puts("");
	return 0;
}

/*

7 7 7 7 7 7

*/

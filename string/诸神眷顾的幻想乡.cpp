#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std; 
const int MaxPoint=4040404;
struct Suffix_AutoMachine{
	int son[MaxPoint][11],pre[MaxPoint],step[MaxPoint],right[MaxPoint],root,num;
	int NewNode(int stp)
	{
		num++;
		memset(son[num],0,sizeof(son[num]));
		pre[num]=0;
		step[num]=stp;
		return num;
	}
	Suffix_AutoMachine()
	{
		num=0;
		root=NewNode(0);
	}
	int push_back(int ch,int p)
	{
		int np=NewNode(step[p]+1);
		right[np]=1;
		while(p&&!son[p][ch])
		{
			son[p][ch]=np;
			p=pre[p];
		}
		if(!p)
			pre[np]=root;
		else
		{
			int q=son[p][ch];
			if(step[q]==step[p]+1)
				pre[np]=q;
			else
			{
				int nq=NewNode(step[p]+1);
				memcpy(son[nq],son[q],sizeof(son[q]));
				step[nq]=step[p]+1;
				pre[nq]=pre[q];
				pre[q]=pre[np]=nq;
				while(p&&son[p][ch]==q)
				{
					son[p][ch]=nq;
					p=pre[p];
				}
			}
		}
		return np;
	}
}S;
struct Edge{
	int to,next;
}e[1010101];
int cnt=0,head[101010];
void add(int u,int v)
{
	cnt++;
	e[cnt].to=v;
	e[cnt].next=head[u];
	head[u]=cnt;
}
int a[101010];
int d[101010];
void dfs(int x,int fa,int p)
{
	int t=S.push_back(a[x],p);
	for(int i=head[x];i!=0;i=e[i].next)
	{
		int to=e[i].to;
		if(to!=fa)
			dfs(to,x,t);
	}
}
int main()
{
	int n,c;
	scanf("%d%d",&n,&c);
	for(int i=1;i<=n;i++)
		scanf("%d",&a[i]);
	for(int i=1;i<n;i++)
	{
		int u,v;
		scanf("%d%d",&u,&v);
		add(u,v);
		add(v,u);
		d[u]++;
		d[v]++;
	}
	for(int i=1;i<=n;i++)
	if(d[i]==1)
		dfs(i,0,1);
	long long ans=0;
	for(int i=2;i<=S.num;i++)
		ans+=S.step[i]-S.step[S.pre[i]];
	printf("%lld\n",ans);
	return 0;
}

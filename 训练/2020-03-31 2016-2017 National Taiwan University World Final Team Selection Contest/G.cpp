#include<bits/stdc++.h>
using namespace std;

struct Node{
	int lst;
	long long val;
};

bool operator < (const Node &A,const Node &B)
{
	return A.val>B.val;
}

priority_queue<Node> Q;

int a[202020];
int main()
{
	int N,K;
	scanf("%d%d",&N,&K);
	for(int i=1;i<=N;i++)
		scanf("%d",&a[i]);
	sort(a+1,a+N+1);
	
	Q.push({1,a[1]});
	
	long long ans=0;
	while(K--)
	{
		Node now=Q.top();
		Q.pop();
		ans=now.val;
		if(now.lst<N)
		{
			Q.push({now.lst+1,now.val-a[now.lst]+a[now.lst+1]});
			Q.push({now.lst+1,now.val+a[now.lst+1]});
		}
	}
	printf("%lld\n",ans);
	return 0;
}

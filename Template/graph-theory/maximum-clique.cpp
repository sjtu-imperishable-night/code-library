#include<iostream>
using namespace std;
int ans;
int num[1010];
int path[1010]; 
int a[1010][1010],n;
bool dfs(int *adj,int total,int cnt)
{
    int i,j,k;
    int t[1010];
    if(total==0)
	{
        if(ans<cnt)
		{
            ans=cnt;
			return 1; 
        }    
        return 0;
    }    
    for(i=0;i<total;i++)
	{
        if(cnt+(total-i)<=ans)
			return 0;
        if(cnt+num[adj[i]]<=ans)
			return 0;
        for(k=0,j=i+1;j<total;j++)
		if(a[adj[i]][adj[j]])
            t[k++]=adj[j];
        if(dfs(t,k,cnt+1))
			return 1;
    }
	return 0;
} 
int MaxClique()
{
    int i,j,k;
    int adj[1010];
    if(n<=0)
		return 0;
    ans=1;
    for(i=n-1;i>=0;i--)
	{
        for(k=0,j=i+1;j<n;j++)
        if(a[i][j])
			adj[k++]=j;
        dfs(adj,k,1);
        num[i]=ans;
    }
    return ans;
}
int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	while(cin>>n)
	{
		if(n==0)
			break;
		for(int i=0;i<n;i++)
		for(int j=0;j<n;j++)
			cin>>a[i][j];
		cout<<MaxClique()<<endl;
	}
	return 0;
}

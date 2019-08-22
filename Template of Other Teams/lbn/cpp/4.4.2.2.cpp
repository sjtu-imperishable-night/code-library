#include<bits/stdc++.h>// NOI2009诗人小G
#define N 123333//f[i]=min(f[j]+|sum[i]-sum[j]+i-j-L-1|^P) 
#define inf 1e18
using namespace std;
typedef long double LD;typedef long long LL;
struct Q{int l,r,id;}q[N];//当前DP的决策区间是[l,r],这部分区间是用f[id]更新的
int n,i,L,P,T,len[N];LD dp[N],sum[N];
char s[33];
LD Pw(LD x){
	if(x<0)x=-x;LD ans=1;
	for(int i=1;i<=P;i++)ans*=x;
	return ans;
}
LD calc(int x,int y){return dp[y]+Pw(sum[x]-sum[y]-L+x-y-1);}
void solve(){
	int h=0,t=0,i,l,r,ans;q[0]={1,n,0};//设初值 
	for(int i=1;i<=n;i++){//DP到第i位,求出第i位的dp值
		for(;i>q[h].r;)h++;//让第i位包含在队首的决策区间里
		dp[i]=calc(i,q[h].id);//用队首被更新的dp[id]去更新dp[i]
		if(calc(n,i)>calc(n,q[t].id))continue;
//如果用队尾的被拿来更新的dp[id]去更新dp[n]比用dp[i]更新dp[n]好，就跳过后面更新决策区间的过程
		for(;i<q[t].l&&calc(q[t].l,i)<calc(q[t].l,q[t].id);)t--;
		l=max(q[t].l,i+1);
//i能拿来更新[i+1,n]的决策，那么我们要找出二分转折点的下界，就是最新的决策区间左端点与i+1的最大值
		r=q[t].r;//上界是最新的决策区间的右端点
		ans=min(n,q[t].r+1); //ans是二分出的转折点的位置
		for(;l<=r;){
			int mid=(l+r)>>1;
			if(calc(mid,i)<calc(mid,q[t].id))r=mid-1,ans=mid;else l=mid+1;
		}
		q[t].r=ans-1;//更新原来的决策区间的右端点
		q[++t]={ans,n,i};//加入第i位的决策区间
    }
	if(dp[n]>inf)puts("Too hard to arrange");else printf("%lld\n",(LL)dp[n]);
	puts("--------------------");
}
int main(){
	for(scanf("%d",&T);T--;solve())
		for(sum[0]=0,scanf("%d%d%d",&n,&L,&P),i=1;i<=n;i++)
	scanf("%s",s),len[i]=strlen(s),sum[i]=sum[i-1]+len[i];
}

//f[i]=max(f[j]+(sum[i]-sum[j]+i-j-1-L)*(sum[i]-sum[j]+i-j-1-L))
//f[j]+(sum[i]-sum[j]+i-j-1-L)*(sum[i]-sum[j]+i-j-1-L)>f[k]+(sum[i]-sum[k]-k-1-L)*(sum[i]-sum[k]+i-k-1-L)
//f[j]-f[k]+(sum[j]+j)^2-(sum[k]+k)^2>(sum[i]+i-1-L)*2(sum[j]+j-k-sum[k])
/X(j,k)=2(sum[j]+j-sum[k]-k),Y(j,k)=f[j]-f[k]+(sum[j]+j)^2-(sum[k]+k)^2
#include<cstdio>// HNOI2008玩具装箱
typedef long long LL;LL dp[50050];int n,L,i,h,t,sum[50050],q[50050];
LL DP(LL j,LL i){return dp[j]+(sum[i]-sum[j]+i-j-1-L)*(sum[i]-sum[j]+i-j-1-L);}
LL Y(LL k,LL j){return dp[j]+(sum[j]+j)*(sum[j]+j)-dp[k]-(sum[k]+k)*(sum[k]+k);}
LL X(LL k,LL j){return 2*(sum[j]+j-sum[k]-k);}
int main(){//用一个单调队列来维护解集
	for(scanf("%d%d",&n,&L),i=1;i<=n;i++)scanf("%d",&sum[i]),sum[i]+=sum[i-1];
	for (i=1;i<=n;q[++t]=i++){
//从队头开始，如果已有元素a b c，当i点要求解时，如果g[b,a]<sum[i]，那么说明b点比a点更优，a点可以排除，于是a出队
		for(;h<t&&Y(q[h],q[h+1])<(sum[i]+i-1-L)*X(q[h],q[h+1]);h++);
		for(dp[i]=DP(q[h],i);h<t&&Y(q[t-1],q[t])*X(q[t],i)>=X(q[t-1],q[t])*Y(q[t],i);t--);
	}
//假设队列中从头到尾已经有元素a b c。那么当d要入队的时候，我们维护队列的上凸性质。
//即如果g[d,c]<g[c,b]，那么就将c点删除。直到找到g[d,x]>=g[x,y]为止，并将d点加入在该位置中
	printf("%lld",dp[n]);
}

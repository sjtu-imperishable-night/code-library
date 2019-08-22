LL get(int n,int m){//询问n,m
	LL ans=0;int i,la;
	if(n>m)swap(n,m);//取小的，避免出错
	for(i=1;i<=n;i=la+1){//分块处理，时间复杂度O(n^0.5)
		la=min(n/(n/i),m/(m/i));//对于x∈[i,la]的,n/x和m/x都相等，一起处理
		ans+=1ll*(sum[la]-sum[i-1])*(n/i)*(m/i);//sum为预处理出的前缀和
	}
	return ans;
}

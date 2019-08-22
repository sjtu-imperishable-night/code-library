for(i=1;i<1<<n;i++){//时间复杂度O(n*2^n)
	for(j=0;j<n;j++)if(i>>j&1)
		//f[i-(1<<j)]转移到f[i]
}

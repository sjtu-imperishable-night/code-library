int getk(int k){//求第K大值 
	int v=0,p;k--;
	for(p=N/2;p;p>>=1)if(a[p+v]<=k)k-=a[v+=p];
	return v+1;
}

void rotate_calipers(vector<P>a){
	int n=a.size(),i,j=0;
	a.push_back(a[0]);
	for(i=0;i<n;i++){
		for(;cj(a[i+1],a[j+1],a[i])>cj(a[i+1],a[j],a[i]);j=(j+1)%n;
		ans=max(ans,max(dis(a[i],a[j]),dis(a[i+1],a[j+1]));//最远点对
	}
}

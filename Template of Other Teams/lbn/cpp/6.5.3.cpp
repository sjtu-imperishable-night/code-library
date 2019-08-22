P get_core(vector<P> a){
	int n=a.size();P G=P(0,0);
	D s=polygon_area(a);
	for(i=0;i<n;i++)G=G+(a[i]+a[(i+1)%n])*cj(a[i],a[(i+1)%n]);
	return G/6.0;
}

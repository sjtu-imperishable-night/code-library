LL G(LL n,LL a,LL d,LL m){
	if(d==0)return n*(a/m);
	if(a>=m)return n*(a/m)+G(n,a%m,d,m);
	if(d>=m)return n*(n-1)/2*(d/m)+G(n,a,d%m,m);
	return G((a+d*n)/m,(a+d*n)%m,m,d);
}

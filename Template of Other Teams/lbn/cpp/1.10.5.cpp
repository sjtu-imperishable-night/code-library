int acs(int x){
	int o=0;
	for(;x;x=F[x])sy(x),c[x][1]=o,ps(x),o=x;
	return o;
}
void lca(int x,int y){
	acs(x);return acs(y);
}

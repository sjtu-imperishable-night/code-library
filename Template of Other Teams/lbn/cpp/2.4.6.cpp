int mg(int x,int y,int l,int r){
	if(!x||!y)return x+y;
	if(l==r)return sz[x]+=sz[y],x;
	int md=l+r>>1;
	L[x]=mg(L[x],L[y],l,md);
	R[x]=mg(R[x],R[y],md+1,r);
	return ps(x),x;
}
void add(int&k,int l,int r,int x,int y,int z){
	if(!k)k=++id;
	if(x<=l&&r<=y){ADD(k,z);return;}
	int md=l+r>>1;pd(k);
	if(x<=md)add(L[k],l,md,x,y,z);
	if(y>md)add(R[k],md+1,r,x,y,z);
	ps(k);
}
int qu(int k,int l,int r,int x,int y){
	if(!k)return 0;
	if(x<=l&&r<=y)return V[k];
	int md=l+r>>1,an=0;pd(k);
	if(x<=md)an+=qu(k<<1,l,md,x,y);
	if(y>md)an+=qu(k<<1|1,md+1,r,x,y);
	return an;
}
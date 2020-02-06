int a[N],MX[N],MI[N],S[N],ad[N],cv[N],fcv[N],sz[N],mu[N];
void COV(int k,int z){
	MX[k]=z;MI[k]=z;S[k]=sz[k]*z;
	ad[k]=0;fcv[k]=1;mu[k]=1;cv[k]=z;
}
void MUL(int k,int z){
	MX[k]*=z;MI[k]*=z;S[k]*=z;
	ad[k]*=z;mu[k]*=z;
}
void ADD(int k,int z){
	MX[k]+=z;MI[k]+=z;S[k]+=sz[k]*z;
	ad[k]+=z;
}
void pd(int k){
	if(fcv[k])COV(k<<1,cv[k]),COV(k<<1|1,cv[k]),fcv[k]=0;
	if(mu[k]!=1)MUL(k<<1,mu[k]),MUL(k<<1|1,mu[k]),mu[k]=1;
	if(ad[k])ADD(k<<1,ad[k]),ADD(k<<1|1,ad[k]),ad[k]=0;
}
void ps(int k){
	MI[k]=min(MI[k<<1],MI[k<<1|1]);
	MX[k]=max(MX[k<<1],MX[k<<1|1]);
	S[k]=S[k<<1]+S[k<<1|1];
}
void bd(int k,int l,int r){
	sz[k]=r-l+1;mu[k]=1;
	if(l==r){MX[k]=MI[k]=S[k]=a[l];return;}
	int md=l+r>>1;
	bd(k<<1,l,md);bd(k<<1|1,md+1,r);
	ps(k);
}
void cov(int k,int l,int r,int x,int y,int z){//将[x,y]赋值为z 
	if(x<=l&&r<=y){COV(k,z);return;}
	int md=l+r>>1;pd(k);
	if(x<=md)cov(k<<1,l,md,x,y,z);
	if(y>md)cov(k<<1|1,md+1,r,x,y,z);
	ps(k);
}
void mul(int k,int l,int r,int x,int y,int z){//将[x,y]都乘z
	if(x<=l&&r<=y){MUL(k,z);return;}
	int md=l+r>>1;pd(k);
	if(x<=md)mul(k<<1,l,md,x,y,z);
	if(y>md)mul(k<<1|1,md+1,r,x,y,z);
	ps(k);
}
void add(int k,int l,int r,int x,int y,int z){//将[x,y]都加z 
	if(x<=l&&r<=y){ADD(k,z);return;}
	int md=l+r>>1;pd(k);
	if(x<=md)add(k<<1,l,md,x,y,z);
	if(y>md)add(k<<1|1,md+1,r,x,y,z);
	ps(k);
}
int qusum(int k,int l,int r,int x,int y){//询问和 
	if(x<=l&&r<=y)return S[k];
	int md=l+r>>1,an=0;pd(k);
	if(x<=md)an+=qusum(k<<1,l,md,x,y);
	if(y>md)an+=qusum(k<<1|1,md+1,r,x,y);
	return an;
}
int qumax(int k,int l,int r,int x,int y){//询问最大值 
	if(x<=l&&r<=y)return MX[k];
	int md=l+r>>1;pd(k);
	if(y<=md)return qumax(k<<1,l,md,x,y);
	if(x>md)return qumax(k<<1|1,md+1,r,x,y);
	return max(qumax(k<<1,l,md,x,y),qumax(k<<1|1,md+1,r,x,y));
}
int qumin(int k,int l,int r,int x,int y){//询问最小值 
	if(x<=l&&r<=y)return MI[k];
	int md=l+r>>1;pd(k);
	if(y<=md)return qumin(k<<1,l,md,x,y);
	if(x>md)return qumin(k<<1|1,md+1,r,x,y);
	return min(qumin(k<<1,l,md,x,y),qumin(k<<1|1,md+1,r,x,y));
}

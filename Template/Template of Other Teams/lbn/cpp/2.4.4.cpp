void ps(int k,int l,int r){
	V[k]=min(vb[k],vk[k]*(d[to[r]]-d[to[l]])+vb[k]);
	if(l!=r)V[k]=min(V[k],min(V[k<<1],V[k<<1|1]));
}
void Ad(int k,int l,int r,LL K,LL B){//用B为首项，K为公差的直线更新线段树上的某点 
	if(vk[k]==K||l==r)vb[k]=min(vb[k],B);else{
		int md=l+r>>1;LL L=d[to[md+1]]-d[to[l]];
		if(K<vk[k]&&B<vb[k])vk[k]=K,vb[k]=B;else
			if(K<vk[k]&&B>vb[k])
				if((B-vb[k])<=L*(vk[k]-K))swap(vk[k],K),swap(vb[k],B),Ad(k<<1,l,md,K,B);
				else Ad(k<<1|1,md+1,r,K,B+K*L);
			else 
				if(K>vk[k]&&B<vb[k])if(vb[k]-B+K-vk[k]<=L*(K-vk[k]))Ad(k<<1,l,md,K,B);
				else swap(vk[k],K),swap(vb[k],B),Ad(k<<1|1,md+1,r,K,B+K*L);
	}
	ps(k,l,r);
}
void add(int k,int l,int r,int x,int y,LL K,LL B){//B为首项，K为公差 
	if(x<=l&&r<=y){Ad(k,l,r,K,B+(d[to[l]]-d[to[x]])*K);return;}
	int md=l+r>>1;
	if(x<=md)add(k<<1,l,md,x,y,K,B);
	if(y>md)add(k<<1|1,md+1,r,x,y,K,B);
	ps(k,l,r);
}
void qu(int k,int l,int r,int x,int y)//询问最小值，AN在外面 
	int L=max(l,x),R=min(r,y);
	AN=min(AN,min(vk[k]*(d[to[L]]-d[to[l]]),vk[k]*(d[to[R]]-d[to[l]]))+vb[k]);
	if(x<=l&&r<=y){AN=min(AN,V[k]);return;}
	int md=l+r>>1;
	if(x<=md)qu(k<<1,l,md,x,y);
	if(y>md)qu(k<<1|1,md+1,r,x,y);
}

struct BIT{
	LL a[N],b[N];
	void ad(int x,LL z){for(int i=x;i<=n;i+=i&-i)a[i]+=z,b[i]+=z*(x-1);}
	LL qu(LL x){
		LL v0=0,v1=0;
		for(int i=x;i;i-=i&-i)v0+=a[i],v1+=b[i];
		return x*v0-v1;
	}
	void add(int x,int y,LL z){ad(x,z);ad(y+1,-z);}//在[x,y]加z
	LL sum(int x,int y){return qu(y)-qu(x-1);}//询问[x,y]的和
}V;

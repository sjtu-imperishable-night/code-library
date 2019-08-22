unsigned getbit(unsigned x,unsigned l,unsigned r){return (x<<(31-r))>>(31-r+l);}
struct Bitset{
	unsigned f[N];
	void reset(){memset(f,0,sizeof f);}//清空
	void setBit(int x){f[x>>5]|=1<<(x&31);}//将某一位置1
	int getBit(int x){return (f[x>>5]>>(x&31))&1;}//得到某一位
	void Xor(Bitset&A,int l,int r){//将A ^=f[l,r]
		int ll=0,rr=r-l;
		for(;ll<=rr;){
			int nel=min((l|31),r),nell=min((ll|31),rr),d=min(nel-l,nell-ll);
			nel=l+d;nell=ll+d;
			A.f[ll>>5]^=(getbit(f[l>>5],l&31,nel&31))<<(ll&31);
			l=nel+1;
			ll=nell+1;
		}
	}
}A,B;

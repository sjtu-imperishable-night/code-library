void cdq(int l,int r){//分治[l,r]，用左半边更新右半边
	if(l==r){f[l]=(f[l]+a[l])%M;return;}//l=r时直接返回答案
	int md=l+r>>1,w=0,i,nn;
	static int b[N],c[N],d[N];
	cdq(l,md);
	for(w=0;(1<<w)<(r-l+1);w++);
	nn=1<<w;//求出应该开的长度
	fr(i,nn){
		b[i]=(l+i<=md)?f[l+i]:0;
		c[i]=(l+i+1<=r)?a[i+1]%M:0;
	}
	mul(b,c,d,nn);//套用FFT第三个模板
	for(i=md+1;i<=r;i++)f[i]=(f[i]+d[i-l-1])%M;//更新答案
	cdq(md+1,r);
}
int main(){
	int n,i;
	for(i=1;i<=n;i++)scanf("%d",&a[i]),f[i]=0;
	cdq(1,n);
	printf("%d\n",f[n]);
}

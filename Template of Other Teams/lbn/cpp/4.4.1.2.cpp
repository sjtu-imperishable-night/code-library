//f[i]=min(f[j]+(d[i]-d[j])^2+p)
//对i来说j比k优 2d[i](-d[j]+d[k])<f[k]+d[k]^2-f[j]-f[j]^2
LL DP(int i,int j){return f[j]+P+(L[i]-L[j])*(L[i]-L[j]);}
LL Y(int j,int k){return f[j]+L[j]*L[j]-f[k]-L[k]*L[k];}
LL X(int j,int k){return 2*(L[j]-L[k]);}
void dfs(int x,int fa,int h,int t){//记录队首和队尾
	int i,p;
	f[x]=L[x]*L[x];
	for(;h<t&&Y(q[h],q[h+1])>=L[x]*X(q[h],q[h+1]);h++);
	if(x!=1)f[x]=min(f[x],DP(x,q[h]));
	an=max(an,f[x]);
	for(;h<t&&Y(q[t-1],q[t])*X(q[t],x)>=X(q[t-1],q[t])*Y(q[t],x);t--);
	t++;p=q[t];q[t]=x;//将队尾更改的值记录
	for(int i=fir[x];i;i=ne[i])if(la[i]!=fa)
		L[la[i]]=L[x]+va[i],dfs(la[i],x,h,t);
	q[t]=p;
}

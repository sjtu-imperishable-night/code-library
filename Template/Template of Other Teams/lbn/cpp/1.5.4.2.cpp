int a[N],A[N][N],d[N],fir[N],pre[N],nb[N],la[M],va[M],ne[M],cur[N],q[N];bool v[N];
void ins(int x,int y,int z){
	la[++tot]=y;ne[tot]=fir[x];va[tot]=z;fir[x]=tot;
	la[++tot]=x;ne[tot]=fir[y];va[tot]=0;fir[y]=tot;
}
void dfs(int x){v[x]=1;for(int i=fir[x];i;i=ne[i])if(va[i]&&!v[la[i]])dfs(la[i]);}
void fz(int l,int r){//分治建图
	int i,fl=0,p,u,S,T,L,R;
	if(l==r)return;u=S=a[l];T=a[r];fl=0;
	for(i=2;i<=tot;i+=4)va[i+2]=va[i]=(va[i]+va[i+1]+va[i+2]+va[i+3])/2,va[i+1]=va[i+3]=0;
	for(i=1;i<=n;i++)cur[i]=fir[i],nb[i]=0,d[i]=0,pre[i]=0,v[i]=0;
	for(nb[0]=n;d[S]<n;){
		if(u==T){
			for(p=1e9,i=S;i!=T;i=la[cur[i]])if(va[cur[i]]<p)p=va[cur[u=i]];
			for(fl+=p,i=S;i!=T;i=la[cur[i]])va[cur[i]]-=p,va[cur[i]^1]+=p;
		}
		for(i=cur[u];i;i=ne[i])if(va[i]&&d[la[i]]+1==d[u])break;
		if(i)cur[u]=i,pre[la[i]]=u,u=la[i];else{
			if(0==--nb[d[u]])break;
			for(i=cur[u]=fir[u],p=n;i;i=ne[i])if(d[la[i]]<p&&va[i])p=d[la[i]];
			++nb[d[u]=p+1];if(u!=S)u=pre[u];
        	}
	}
	dfs(S);//找割集合
	L=l,R=r;
	//ADD(S,T,fl);//在最小割树中建边
	for(i=1;i<=n;i++)if(v[i])for(j=1;j<=n;j++)if(!v[j])A[i][j]=A[j][i]=min(A[i][j],fl);//i到j的最小割
	for(i=l;i<=r;i++)if(v[a[i]])q[L++]=a[i];else q[R--]=a[i];
	for(i=l;i<=r;i++)a[i]=q[i];
	fz(l,L-1);fz(R+1,r);
}

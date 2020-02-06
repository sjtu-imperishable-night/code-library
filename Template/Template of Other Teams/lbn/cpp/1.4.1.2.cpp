vector<int>E[N];bool v[N];//未验 
int n1,n2,q[N],lx[N],ly[N],dx[N],dy[N];
bool fd(int x){
	for(int i=0,y;i<E[x].size();i++)
		if(!v[y=E[x][i]]&&dy[y]==dx[x]+1)
			if(v[y]=1,!ly[y]||fd(ly[y]))
				return lx[x]=y,ly[y]=x,1;
}
int match(){
	CL(lx);CL(ly);int an=0,i;
	for(;;){
		bool ff=0;int h=0,t=0,x,y;
		CL(dx);CL(dy);
		for(i=1;i<=n1;i++)if(!lx[i])q[++t]=i;
		for(;h^t;){
			x=q[++h];
			for(i=0;i<E[x].size();i++)
				if(!dy[y=E[x][i]]){
					dy[y]=dx[x]+1;
					if(ly[y]){
						dx[ly[y]]=dy[y]+1;
						q[++t]=ly[y];
					}else ff=1;
				}
		}
		if(!ff)break;
		CL(v);
		for(i=1;i<=n1;i++)if(!lx[i]&&fd(i))an++;
	}
	return an;
}

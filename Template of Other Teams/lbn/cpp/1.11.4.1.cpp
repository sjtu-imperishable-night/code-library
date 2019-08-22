int n,m,X[M],Y[M],tf[N];LL f[N],co[N];//X[i]->Y[i]表示有向边
void graph_hash(int A,int B,int C,int K,int P){//A,B,C,K,P自选
	int q,v,e,i,z;
	for(i=1;i<=n;i++){
		for(q=1;q<=n;q++)f[q]=1;
		for(z=0;z<K;z++){
			memcpy(tf,f,sizeof f);
			for(q=1;q<=n;q++)f[q]*=A;
			for(q=1;q<=m;q++){
				f[X[i]]+=f[Y[i]]*B;
				f[Y[i]]+=f[X[i]]*C;
			}
			f[i]+=D;
			for(q=1;q<=n;q++)f[q]*=P;
		}
		co[i]=f[i];
	}
	sort(co+1,co+n+1);
}

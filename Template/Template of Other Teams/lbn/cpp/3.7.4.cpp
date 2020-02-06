void add(int x){
	p=np;st[np=++cnt]=st[p]+1;
	for(;p&&!c[p][x];p=F[p])c[p][x]=np;V[np]=1;
	if(!p)F[np]=1,lk(np,1);else
	if(st[p]+1==st[q=c[p][x]])F[np]=q,lk(np,q);else{
		st[nq=++cnt]=st[p]+1,memcpy(c[nq],c[q],sizeof c[q]);
		F[nq]=F[q];lk(nq,F[q]);F[np]=F[q]=nq;
		ct(q);lk(q,nq);lk(np,nq);
		for(;c[p][x]==q;p=F[p])c[p][x]=nq;
	}
}

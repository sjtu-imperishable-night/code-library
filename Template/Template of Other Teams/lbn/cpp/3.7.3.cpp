void add(int x){//广义后缀自动机在后面加入一个字符x，注意新开串时np设为1
	p=np;np=c[p][x];
	if(!np||st[np]!=st[p]+1){
		st[np=++cnt]=st[p]+1;
		if(!p)F[np]=1;else 
		if(st[p]+1==st[q=c[p][x]])F[np]=q;else{
			st[nq=++cnt]=st[p]+1;memcpy(c[nq],c[q],sizeof c[q]);
			F[nq]=F[q];F[q]=F[np]=nq;
			for(;p&&c[p][x]==q;p=F[p])c[p][x]=nq;
		}
	}
}

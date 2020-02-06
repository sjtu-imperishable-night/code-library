C minumum_circle(vector<P>p){
	C a;int i,j,k,n=(int)p.size();
	random_shuffle(p.begin(),p.end());
	for(i=0;i<n;i++)if(!in_circle(p[i],a)){
		a=C(p[i],0);
		for(j=0;j<i;j++)if(!in_circle(p[j],a)){
			a=make_circle(p[j],p[i]);
			for(k=0;k<j;k++)
				if(!in_circle(p[k],a))a=make_circle(p[i],p[j],p[k]);
		}
	}
	return a;
}
